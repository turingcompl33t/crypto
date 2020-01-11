# encrypt.py
# Simple test of RSA encryption / decryption.

import sys

from util import read_key_file
from rsa import rsa_encrypt, rsa_decrypt

# default keyfile names
PUBKEY_FILE  = "key.pub"
PRIVKEY_FILE = "key.priv"

def main():
    (n, e, N) = read_key_file(PUBKEY_FILE)
    (n, d, N) = read_key_file(PRIVKEY_FILE)

    pt = "hello world".encode("utf-8")

    # do the thing
    ct = rsa_encrypt(pt, n, (e, N))
    nt = rsa_decrypt(ct, n, (d, N))

    # how did we do?
    print("plaintext in:")
    hexdump(pt, 32)
    print("ciphertext (padded):")
    hexdump(ct, 32)
    print("plaintext out:")
    hexdump(nt, 32)

# pretty print in hexadecimal format
def hexdump(bytes, w):
    l = len(bytes)
    for i in range(0, l, w):
        j = i
        while j < (i + w) and j < l:
            str = "0x" + "{0:02x}".format(bytes[j]) + " "
            sys.stdout.write(str)
            j += 1
        sys.stdout.write("\n")
    sys.stdout.flush()

if __name__ == "__main__":
    main()
