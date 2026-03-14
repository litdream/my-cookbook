import random
import sys

class DHParameters:
    """Represents the public parameters for Diffie-Hellman: a prime p and a generator g."""
    def __init__(self, p, g):
        self.p = p
        self.g = g

    def __str__(self):
        return f"Public Parameters: (p={self.p}, g={self.g})"

class Peer:
    """Represents a participant in the Diffie-Hellman key exchange."""
    def __init__(self, name, params):
        self.name = name
        self.params = params
        self._private_key = None
        self.public_key = None
        self.shared_secret = None

    def generate_private_key(self):
        """Step 1: Each peer generates a secret private key."""
        # In a real scenario, this would be a very large random number.
        self._private_key = random.randint(2, self.params.p - 2)
        print(f"[Step] {self.name} generates a secret private key: (hidden)")
        return self._private_key

    def generate_public_key(self):
        """Step 2: Each peer calculates their public key from the private key."""
        # A = g^a mod p
        self.public_key = pow(self.params.g, self._private_key, self.params.p)
        print(f"[Step] {self.name} calculates public key: {self.params.g}^{self.name}_private mod {self.params.p} = {self.public_key}")
        return self.public_key

    def compute_shared_secret(self, remote_public_key):
        """Step 4: Each peer calculates the shared secret using the other's public key."""
        # s = B^a mod p
        self.shared_secret = pow(remote_public_key, self._private_key, self.params.p)
        print(f"[Step] {self.name} computes shared secret: {remote_public_key}^{self.name}_private mod {self.params.p} = {self.shared_secret}")
        return self.shared_secret

def run_simulation(message):
    print("--- Diffie-Hellman Key Exchange Simulator ---")
    print("Educational simulation of how two parties establish a shared secret over an insecure channel.\n")

    # 1. Agree on public parameters
    # In practice, these are standard large primes. Here we use slightly larger ones for a realistic feel.
    p = 1019  # A safe prime number
    g = 2     # A generator
    params = DHParameters(p, g)
    print(f"1. Setup: Both parties agree on public parameters.")
    print(f"   {params}\n")

    # 2. Initialize Peers
    alice = Peer("Alice", params)
    bob = Peer("Bob", params)

    # 3. Private Key Generation
    print("2. Private Key Generation (Local & Secret):")
    alice.generate_private_key()
    bob.generate_private_key()
    print()

    # 4. Public Key Calculation
    print("3. Public Key Calculation (Based on private key):")
    alice_pub = alice.generate_public_key()
    bob_pub = bob.generate_public_key()
    print()

    # 5. Public Key Exchange
    print("4. Public Key Exchange (Sent over insecure channel):")
    print(f"   Alice sends public key {alice_pub} to Bob.")
    print(f"   Bob sends public key {bob_pub} to Alice.\n")

    # 6. Shared Secret Computation
    print("5. Shared Secret Computation (The Magic):")
    alice_secret = alice.compute_shared_secret(bob_pub)
    bob_secret = bob.compute_shared_secret(alice_pub)
    print()

    # 7. Verification
    print("6. Result Verification:")
    if alice_secret == bob_secret:
        print(f"   SUCCESS! Both Alice and Bob have established the same shared secret: {alice_secret}")
        print("   An eavesdropper only knows p, g, and the public keys, but cannot easily derive this secret.\n")
    else:
        print("   FAILURE! The shared secrets do not match.")
        return

    # 8. Secure Message Exchange
    print("7. Secure Message Exchange (Using the Shared Secret):")
    print(f"   Alice wants to send a plain-text message to Bob: \"{message}\"")
    
    # Simple "encryption" using the shared secret as an XOR mask.
    # In a real application, you would use a robust cipher like AES with this secret.
    try:
        # If the message is numeric, we can demonstrate with a direct XOR.
        msg_val = int(message)
        encrypted = msg_val ^ alice_secret
        print(f"   Alice encrypts the message: {msg_val} XOR {alice_secret} = {encrypted}")
        print(f"   Alice sends the encrypted value {encrypted} to Bob over the insecure channel.")
        
        decrypted = encrypted ^ bob_secret
        print(f"   Bob receives {encrypted} and decrypts it: {encrypted} XOR {bob_secret} = {decrypted}")
        result_msg = str(decrypted)
    except ValueError:
        # If it's a string, we XOR each character.
        encrypted_chars = [chr(ord(c) ^ (alice_secret % 256)) for c in message]
        encrypted_str = "".join(encrypted_chars)
        print(f"   Alice encrypts the string by XORing each character with (shared_secret % 256).")
        print(f"   Alice sends the encrypted message (in hex): {encrypted_str.encode(errors='replace').hex()}")
        
        decrypted_chars = [chr(ord(c) ^ (bob_secret % 256)) for c in encrypted_str]
        decrypted = "".join(decrypted_chars)
        print(f"   Bob receives the data and decrypts it: \"{decrypted}\"")
        result_msg = decrypted

    if result_msg == message:
        print(f"\n   FINAL RESULT: Bob successfully received the plain-text message: \"{result_msg}\"")
        print("   Even though they never sent the message in plain-text or shared the key!")

if __name__ == "__main__":
    # Use the first command line argument as the message, or a default value.
    input_message = sys.argv[1] if len(sys.argv) > 1 else "1234567"
    run_simulation(input_message)
