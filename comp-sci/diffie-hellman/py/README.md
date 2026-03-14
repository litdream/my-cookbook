# Diffie-Hellman Key Exchange Simulator

This project is an educational simulator for the Diffie-Hellman key exchange algorithm. It demonstrates how two parties (Alice and Bob) can establish a shared secret over an insecure communication channel without ever sharing their private keys.

## How it Works

1.  **Public Parameters**: Both parties agree on a large prime number `p` and a base `g` (generator).
2.  **Private Keys**: Each party generates a secret private key (`a` for Alice, `b` for Bob).
3.  **Public Keys**:
    - Alice calculates `A = g^a mod p` and sends it to Bob.
    - Bob calculates `B = g^b mod p` and sends it to Alice.
4.  **Shared Secret**:
    - Alice calculates `s = B^a mod p`.
    - Bob calculates `s = A^b mod p`.
    - Both results will be identical: `s = (g^b)^a mod p = (g^a)^b mod p = g^{ab} mod p`.

## Running the Simulator

To run the simulation with a specific message:

```bash
python3 simulator.py 1234567
```

If no argument is provided, it defaults to "1234567". It supports both numeric and string messages.

## Parameters

The simulator uses mathematically sound parameters for demonstration:
- **p**: 1019 (A safe prime)
- **g**: 2 (A generator)

## Object-Oriented Design

- `DHParameters`: Stores the public prime `p` and generator `g`.
- `Peer`: Represents a participant (e.g., Alice or Bob), managing their private key, public key, and the computation of the shared secret.
