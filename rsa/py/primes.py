# primes.py
# Utility module for working with large prime numbers.

from util import modexp
from random import getrandbits, randrange

# generate a random prime of k bits
def primegen(k):
    p = get_candidate(k)
    while not is_prime(p):
        # prime number theorem guarantees that no matter where we start,
        # we are always "in the neighborhood" of some prime
        p -= 2

    return p

# primality test for arbitrary integers, using two-step filter
def is_prime(n):
    if n == 2 or n == 3:
        return True
    if n <= 1 or (n % 2) == 0:
        return False

    # first filter stage: testing divisibility by small primes (odds)
    # range of odd numbers chosen (arbitrarily) to be 3 -> 1000
    for p in range(5, 1000, 2):
        if n % p == 0:
            return p == n

    # second filter stage: miller-rabin primality test
    return miller_rabin(n)

# miller-rabin probabilistic primality test
# implemented directly from algorithm description in
#   Cryptography Engineering (Ferguson, Schneier, Kohno)
# IDEA: We choose a random value a < n, called the basis,
# and check a certain property of a modulo n that holds whenever
# n is prime; when n is not prime, this property holds
# for at most 25% of all possible basis values a.
# We repeat the test for multiple basis values a
# to increase our confidence in the result.
def miller_rabin(n, k=128):
    # compute (s, r) such that r is odd, (2^r)s = n - 1
    (s, r) = (0, n - 1)
    while r & 1 == 0:
        s += 1
        r //= 2

    # track probability of false result, k
    # probability is at most 2^(-k)
    # loop until this probability is small enough for our security goal
    for _ in range(k):
        # choose random a such that 2 <= a <= n - 1
        a = randrange(2, n - 1)
        # expensive operation: modular exponentiation
        x = modexp(a, r, n)

        # when x = 1, test passes for basis a
        if x != 1 and x != (n - 1):
            # the sequence x, x^2, ..., x^(2^r) must finish on value 1
            # and furthermore the last value not equal to 1 must be n - 1 if n prime
            i = 1
            while i < s and x != (n - 1):
                x = modexp(x, 2, n)
                if x == 1:
                    return False
                i += 1
            if x != (n - 1):
                return False

        # n has passed the primality test for basis a;
        # we have reduced the probability of a false result by 2^2

    return True

# generate an odd prime candidate of k bits
def get_candidate(k):
    p = getrandbits(k)
    # bitwise mask to ensure MSB = 1, LSB = 1
    p |= (1 << (k - 1) | 1)
    return p
