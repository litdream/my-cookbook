import socket
import ssl
import urllib.parse
from typing import Tuple, Dict, Optional

# --- Configuration ---
HOST = 'google.com'
MAX_REDIRECTS = 5 # Maximum number of redirects to follow

# Helper function to parse raw HTTP response bytes
def parse_http_response(response_data: bytes) -> Tuple[Optional[int], Dict[str, str], str]:
    """
    Parses the raw byte response into status code, headers, and body.
    """
    try:
        # Decode the bytes and find the end of the headers (\r\n\r\n)
        response_text = response_data.decode('utf-8', errors='ignore')
        header_end = response_text.find('\r\n\r\n')

        if header_end == -1:
            print("Warning: Could not find header/body separator.")
            return None, {}, response_text

        headers_text = response_text[:header_end]
        body = response_text[header_end + 4:]

        # Split into lines to parse status and headers
        lines = headers_text.split('\r\n')
        status_line = lines[0]
        
        parts = status_line.split(' ', 2)
        status_code = int(parts[1]) if len(parts) > 1 else None

        headers = {}
        for line in lines[1:]:
            if ': ' in line:
                key, value = line.split(': ', 1)
                headers[key.lower()] = value.strip()
        
        return status_code, headers, body

    except Exception as e:
        print(f"Error parsing HTTP response: {e}")
        return None, {}, response_data.decode('utf-8', errors='ignore')


def fetch_https_page(url: str, max_redirects: int = MAX_REDIRECTS) -> Tuple[Optional[int], Dict[str, str], str]:
    """
    Simulates a curl request, including automatic redirection handling, 
    by establishing a secure TLS connection and fetching the final HTTP response.
    """
    
    current_url = url
    print(f"--- Starting HTTPS Fetch with Redirect Following (Max: {max_redirects}) ---")

    for redirect_count in range(max_redirects + 1):
        print(f"\n[{redirect_count + 1}/{max_redirects + 1}] Target URL: {current_url}")

        # 1. Parse the current URL to get components
        try:
            parsed_url = urllib.parse.urlparse(current_url)
            scheme = parsed_url.scheme.lower()
            host = parsed_url.netloc
            # Path must include query and be at least '/'
            path = parsed_url.path
            if not path:
                path = '/'
            if parsed_url.query:
                path += '?' + parsed_url.query
            
            if scheme not in ('http', 'https'):
                print(f"Error: Unsupported scheme '{scheme}'. Must be http or https.")
                return None, {}, "Unsupported scheme."

            port = 443 if scheme == 'https' else 80
            
            if not host:
                print("Error: Could not determine host from URL.")
                return None, {}, "Invalid URL."

        except Exception as e:
            print(f"Error parsing URL '{current_url}': {e}")
            return None, {}, f"URL parsing error: {e}"

        # 2. Prepare the HTTP GET request
        http_request = (
            f"GET {path} HTTP/1.1\r\n"
            f"Host: {host}\r\n"
            f"User-Agent: SimulatedCurlPrototype/1.0 (Redirect {redirect_count})\r\n"
            f"Connection: close\r\n"
            f"\r\n"
        )
        request_bytes = http_request.encode('utf-8')

        # 3. Resolve DNS
        print(f"  Attempting to resolve IP address for {host}...")
        try:
            ip = socket.gethostbyname(host)
            print(f"  Resolved to IP: {ip}")
        except socket.gaierror as e:
            print(f"  Error resolving host: {e}")
            return None, {}, "DNS resolution failed."

        # 4. Create and Connect Socket
        raw_sock = None
        ssl_sock = None
        try:
            print("  Creating raw TCP socket...")
            raw_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            raw_sock.settimeout(10) # Set a generous timeout

            if scheme == 'https':
                # 5. Wrap with TLS/SSL context
                print("  Wrapping socket with TLS/SSL context...")
                context = ssl.create_default_context()
                # The 'server_hostname' is vital for certificate validation (crypto part)
                ssl_sock = context.wrap_socket(raw_sock, server_hostname=host)
            else:
                ssl_sock = raw_sock # Use raw socket for HTTP

            # 6. Connect the secure socket (also performs TLS handshake if HTTPS)
            print(f"  Connecting to {host}:{port}...")
            ssl_sock.connect((host, port))
            print("  Connection and TLS Handshake successful.")
            
            # 7. Send the HTTP request
            print(f"  Sending HTTP Request for {path}...")
            ssl_sock.sendall(request_bytes)

            # 8. Receive the response
            print("  Receiving HTTP Response...")
            response_data = b""
            while True:
                chunk = ssl_sock.recv(4096)
                if not chunk:
                    break
                response_data += chunk
            
        except socket.timeout:
            print("  Error: Socket timeout reached.")
            return None, {}, "Socket timeout."
        except socket.error as e:
            print(f"  Error connecting or during data transfer: {e}")
            return None, {}, "Connection error."
        except Exception as e:
            print(f"  An unexpected error occurred: {e}")
            return None, {}, "Unexpected error."
        finally:
            if ssl_sock:
                ssl_sock.close()

        # 9. Parse and Check for Redirect
        status_code, headers, body = parse_http_response(response_data)
        
        print(f"  Received Status Code: {status_code}")
        
        if status_code in (301, 302, 303, 307, 308) and 'location' in headers:
            location = headers['location']
            print(f"  Redirect detected. Following new location: {location}")
            
            if redirect_count >= max_redirects:
                print(f"  Redirect limit ({max_redirects}) reached. Stopping.")
                return status_code, headers, body
            
            # Update the URL and continue the loop
            current_url = location
            continue

        # 10. Not a redirect, return the final response
        print("  Final response received (Status not 3xx).")
        return status_code, headers, body

    # Fallback if loop condition fails unexpectedly
    return None, {}, f"Maximum redirect limit ({max_redirects}) reached."


# Execute the simulation
if __name__ == "__main__":
    START_URL = f"https://{HOST}/"
    
    status, headers, body = fetch_https_page(START_URL)

    if status:
        print("\n" + "="*50)
        print("=== FINAL RESULT AFTER REDIRECTS ===")
        print(f"Final Status: {status}")
        print("Final Headers:")
        for k, v in headers.items():
            print(f"  {k}: {v}")
        print("\nBody (Index File Snippet - First 500 chars):")
        # Print only a snippet of the body
        print(body[:500].strip() + ('...' if len(body) > 500 else ''))
        print("="*50)
    else:
        print("\nFailed to retrieve final content.")
