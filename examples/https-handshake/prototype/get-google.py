import socket
import ssl

# --- Configuration ---
HOST = 'google.com'
PORT = 443  # Standard port for HTTPS (TLS/SSL)

# The request we want to send, including the necessary Host header.
# We are asking for the root resource ('/')
HTTP_REQUEST = (
    f"GET / HTTP/1.1\r\n"
    f"Host: {HOST}\r\n"
    f"User-Agent: SimulatedCurlPrototype/1.0\r\n"
    f"Connection: close\r\n"
    f"\r\n"
)

def fetch_https_page(host, port, request):
    """
    Simulates a curl request by establishing a TCP connection and then
    upgrading it to a secure TLS connection to fetch an HTTP response.
    """
    print(f"1. Attempting to resolve IP address for {host}...")
    try:
        # Resolve the hostname to an IP address (DNS lookup simulation)
        ip = socket.gethostbyname(host)
        print(f"   Resolved to IP: {ip}")
    except socket.gaierror as e:
        print(f"Error resolving host: {e}")
        return

    # 2. Create a basic TCP socket (AF_INET for IPv4, SOCK_STREAM for TCP)
    # This is the raw transport layer.
    print("3. Creating raw TCP socket...")
    try:
        raw_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        raw_sock.settimeout(5) # Set a timeout for connection and reads
    except Exception as e:
        print(f"Error creating socket: {e}")
        return

    # 4. Wrap the socket with an SSL context.
    # This context handles the negotiation of the TLS handshake and the encryption/decryption.
    context = ssl.create_default_context()
    print(f"4. Wrapping socket with TLS/SSL context...")
    
    # Use context.wrap_socket() to perform the TLS handshake immediately upon connection.
    # The 'server_hostname' is crucial for SNI (Server Name Indication) and certificate validation.
    try:
        ssl_sock = context.wrap_socket(raw_sock, server_hostname=host)
    except Exception as e:
        print(f"Error creating SSL wrapper: {e}")
        raw_sock.close()
        return

    # 5. Connect the secure socket (this also completes the TLS handshake)
    # [Image of TLS handshake process]
    print(f"5. Connecting secure socket to {host}:{port}...")
    try:
        ssl_sock.connect((host, port))
        print("   Connection and TLS Handshake successful.")
    except socket.error as e:
        print(f"Error connecting or during TLS handshake: {e}")
        ssl_sock.close()
        return


    # 6. Send the HTTP GET request over the encrypted channel
    request_bytes = request.encode('utf-8')
    print("\n6. Sending HTTP Request (Encrypted):")
    print("-" * 20)
    print(request)
    print("-" * 20)
    
    try:
        ssl_sock.sendall(request_bytes)
    except Exception as e:
        print(f"Error sending data: {e}")
        ssl_sock.close()
        return

    # 7. Receive and decode the response
    print("7. Receiving HTTP Response (Decrypted):")
    response_data = b""
    while True:
        try:
            # Read a small chunk of data (up to 4096 bytes)
            chunk = ssl_sock.recv(4096)
            if not chunk:
                # No more data means the server closed the connection
                break
            response_data += chunk
        except socket.timeout:
            print("   Timeout reached during read.")
            break
        except Exception as e:
            print(f"Error receiving data: {e}")
            break

    # 8. Print the received content
    print("-" * 50)
    try:
        # Decode the byte data to a string
        decoded_response = response_data.decode('utf-8', errors='ignore')
        print(decoded_response)
    except Exception as e:
        print(f"Error decoding response: {e}")
        
    print("-" * 50)
    print(f"\n8. Total bytes received: {len(response_data)}")

    # 9. Close the connection
    ssl_sock.close()
    print("9. Connection closed.")


# Execute the simulation
if __name__ == "__main__":
    fetch_https_page(HOST, PORT, HTTP_REQUEST)
