# util.py
# Miscellaneous utility functions for working with the RSA cryptosystem.

# -----------------------------------------------------------------------------
#   Exported Functions

# compute GCD via Euclid's Algorithm
def gcd(o1, o2):
    if o1 % o2 == 0:
        return o2
    else:
        return gcd(o2, o1 % o2)

# compute multiplicative inverse of a modulo n
# IDEA: the Extended Euclidean Algorithm allows us to compute
# the multiplicative inverse of a modulo n efficiently.
# EEA gives us an algorithm to compute gcd(n, a) = s*n + t*a
# we know that a must be relatively prime to n, so gcd(n, a) = 1
# thus: 1 = s*n + t*a
#   =>  s*n + t*a = 1 mod n
#   =>  t*a = 1 mod n
#   =>  t = a^(-1)
#   =>  t is exactly the multiplicative inverse we are looking for
def modinv(a, n):
    # initialize the 'lookback' variables s_i, t_i
    (s_i2, s_i1, s_i) = (1, 0, 0)
    (t_i2, t_i1, t_i) = (0, 1, 0)

    q   = 0
    tmp = 0

    while True:
        if n % a == 0:
            return t_i
        tmp = a
        q   = n // a
        a   = n % a
        n   = tmp

        # update for the next phase
        s_i = s_i2 - q*s_i1
        t_i = t_i2 - q*t_i1

        s_i2 = s_i1
        s_i1 = s_i
        t_i2 = t_i1
        t_i1 = t_i

# compute b^e mod n by square and multiply
def modexp(b, e, n):
    x = bin(e)[2:]
    y = b
    z = 1
    for i in range(len(x) - 1, -1, -1):
        if x[i] == "1":
            z = z*y % n
        y = y*y % n
    return z

# compute b^e mod n recursively
def modexp_r(b, e, n):
    if e == 0:
        return 1
    elif e % 2 == 0:
        y = modexp_r(b, e/2, n)
        return (y * y) % n
    else:
        return (modexp_r(b, e-1, n) * b) % n

# convert integer in decimal format to byte array
def int_to_bytes(n):
    pass
    # place MSB at position 0

# convert byte array to integer in decimal format
def bytes_to_int(b):
    pass
    # assume the MSB is at position 0

# -----------------------------------------------------------------------------
#   File I/O

# read RSA key from file
def read_key_file(fn):
    with open(fn, "r") as f:
        params = f.read().split('\n')

    return (int(params[0]), int(params[1]), int(params[2]))

# write RSA key to file
def write_key_file(fn, params):
    (n, exp, N) = params

    with open(fn, "w") as f:
        f.write(str(n)   + "\n")
        f.write(str(exp) + "\n")
        f.write(str(N)   + "\n")

# -----------------------------------------------------------------------------
#   Quicktest Script

def main():
    a = modinv(301, 973)
    print(a)

if __name__ == "__main__":
    main()
