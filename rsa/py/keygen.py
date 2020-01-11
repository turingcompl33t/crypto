# keygen.py
# RSA key pair generation script.

from rsa import rsa_keygen
from util import write_key_file

# default keyfile names
PUBKEY_FILE  = "key.pub"
PRIVKEY_FILE = "key.priv"

# the size of the modulus to use for key generation, in bits
MODULUS_SIZE = 2048

def keygen():
    # generate an RSA public / private keypair
    (e, d, N) = rsa_keygen(MODULUS_SIZE)

    # write the keypairs to file
    write_key_file(PUBKEY_FILE,  (MODULUS_SIZE, e, N))
    write_key_file(PRIVKEY_FILE, (MODULUS_SIZE, d, N))

if __name__ == "__main__":
    keygen()
