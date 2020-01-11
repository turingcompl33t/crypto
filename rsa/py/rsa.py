# rsa.py
# RSA in python.

import sys
from random import randint

from primes import primegen
from util import gcd, modinv, modexp

# -----------------------------------------------------------------------------
#   Exported Functions

# generate RSA key values: e, d, N
def rsa_keygen(n):
    # choose random primes p,q on the order of n / 2 bits
    p = primegen(n // 2)
    q = primegen(n // 2)

    # compute N as product of p,q
    N = p*q

    # compute phi(n)
    pN = (p - 1) * (q - 1)

    # choose public exponent e:
    # must be relatively prime with phi(N)
    e = 3
    while gcd(pN, e) != 1:
        e += 1

    # compute private exponent d:
    # the multiplicative inverse of e, modulo phi(N)
    d = modinv(e, pN)
    while d < 0:   # we want a positive value for d; working modulo phi(N),
        d += pN    # all values d_i = d + k*phi(N) for integer k are equivalent

    # return the components of RSA key
    return (e, d, N)

# encrypt plaintext m under RSA public key
def rsa_encrypt(pt, n, pubkey):
    # extract the public key
    (e, N) = pubkey

    # pad the input plaintext
    padded = rsa_pad_pkcs(pt, n)

    # convert byte-string to integer representation
    m = int.from_bytes(padded, byteorder="big")

    # compute the RSA function
    ct = rsa_func(m, e, N)

    # convert to bytes on return
    return ct.to_bytes(n >> 3, byteorder="big")

# decrypt ciphertext c under RSA private key
def rsa_decrypt(ct, n, privkey):
    # extract the private key
    (d, N) = privkey

    # convert byte string to integer representation
    c = int.from_bytes(ct, byteorder="big")

    # compute the RSA function
    pt = rsa_func(c, d, N)

    # convert to bytes
    padded = pt.to_bytes(n >> 3, byteorder="big")

    # verify padding
    pt = rsa_strip_pkcs(padded, n)
    if pt is None:
        print("Invalid Padding")

    return pt

# -----------------------------------------------------------------------------
#   Private Functions

# compute the RSA trapdoor function: b^e mod N
def rsa_func(b, e, N):
    return modexp(b, e, N)

# pad message in PKCS#1 v1.5 format
def rsa_pad_pkcs(pt, modsize):
    k = modsize >> 3

    # length of data must not be more than k - 11 octets
    # where k = size of the modulus, in bytes
    assert len(pt) <= (k - 11)

    # overall format:
    # EB = 00 | BT | PS | 00 | D

    # total length of the padded message is byte length of modulus
    padded = bytearray(k)

    padded[0] = 0x00  # 00: constant 0x00
    padded[1] = 0x02  # BT: PKCS#1 v1.5 block type 2

    # PS: random, nonzero padding bytes
    pslen = (k - 3 - len(pt))
    for i in range(2, 2 + pslen):
        padded[i] = randint(1, 255)

    # 00: constant 0x00
    padded[2+pslen] = 0x00

    # D: complete the padded block with the plaintext data
    for (i, j) in list(zip(range(2 + pslen + 1, k), range(len(pt)))):
        padded[i] = pt[j]

    return padded

# validate PKCS#1 v1.5 message padding and strip from message
def rsa_strip_pkcs(padded, modsize):
    k = modsize >> 3

    # check for valid PKCS#1 v1.5 block type 2 padding
    if padded[0] != 0x00 or padded[1] != 0x02:
        return None

    # padding is validated; strip off random pad bytes until 0x00 byte
    offset = 2
    while padded[offset] != 0x00:
        offset += 1
    offset += 1

    # initialize a new byte array for stripped message
    pt = bytearray(k - offset)

    # and populate the new byte array
    for (i, j) in list(zip(range(len(pt)), range(offset, k))):
        pt[i] = padded[j]

    return pt
