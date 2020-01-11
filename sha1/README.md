### SHA-1 Implementation

An implementation of the SHA-1 hash function, as described in [FIPS 180-2](https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf) — the "Secure Hash Standard". 

Note that this implementation attempts to maximize the 'comprehensibility' of the hash algorithm; much is left to be desired in terms of optimization. 

### Build

For a standard test run:

```
$ make
```

For a test run with debugging output:

```
$ make debug
``` 

To clean up after yourself:

```
$ make clean
```

### Correctness

Compare the following output with the sample algorithm traces included in [the standard](https://csrc.nist.gov/csrc/media/publications/fips/180/2/archive/2002-08-01/documents/fips180-2.pdf). 

```
input:
  abc
digest:
  a9993e36 4706816a ba3e2571 7850c26c 9cd0d89d 
input:
  abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq
digest:
  84983e44 1c3bd26e baae4aa1 f95129e5 e54670f1 
```
