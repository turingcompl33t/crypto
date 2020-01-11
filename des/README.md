### DES Implementation

An implementation of the Data Encryption Standard (DES) block cipher, as described in [FIPS Publication 46-3](https://csrc.nist.gov/csrc/media/publications/fips/46/3/archive/1999-10-25/documents/fips46-3.pdf) (reaffirmed October 1996, withdrawn May 2005). 

Note that this implementation attempts to maximize the 'comprehensibility' of the cipher algorithm; much is left to be desired in terms of optimization. 

### Build

For a standard DES run:

```
$ make testdes
```

For a DES run with debugging/trace output:

```
$ make debugdes
``` 

For a standard 3DES run:

```
$ make test3des
```

For a 3DES run with debugging/trace output:

```
$ make debug3des
``` 

To generate test vector for the DES feistel construction:

```
$ make tracefesitel
```

To generate test vector for the DES function:

```
$ make tracefunc
```

To clean up after yourself:

```
$ make clean
```

### Traces

One of the first things I look for when I want to implement an algorithm from scratch are some existing test vectors against which I can verify my implementation. For newer ciphers like AES, these are easy to come by, and are often embedded in the specification of the cipher itself. Intererstingly, I had a difficult time finding test vectors for DES published by reliable sources. 

Thus I chose to include functionality to generate cipher traces for various components of the DES cipher. 

A sample test vector for DES encryption / decryption:

```
$ ./debug 
[DEBUG] DES ENCRYPT
PLAINTEXT:          12 34 56 ab cd 13 25 36 
KEY:                aa bb 09 18 27 36 cc dd 
IP:                 14 a7 d6 78 18 ca 18 ad 
( 1) STATE:         18 ca 18 ad 5a 78 e3 94 
( 1) SUBKEY:        19 4c d0 72 de 8c 
( 2) STATE:         5a 78 e3 94 4a 12 10 f6 
( 2) SUBKEY:        45 68 58 1a bc ce 
( 3) STATE:         4a 12 10 f6 b8 08 95 91 
( 3) SUBKEY:        06 ed a4 ac f5 b5 
( 4) STATE:         b8 08 95 91 23 67 79 c2 
( 4) SUBKEY:        da 2d 03 2b 6e e3 
( 5) STATE:         23 67 79 c2 a1 5a 4b 87 
( 5) SUBKEY:        69 a6 29 fe c9 13 
( 6) STATE:         a1 5a 4b 87 2e 8f 9c 65 
( 6) SUBKEY:        c1 94 8e 87 47 5e 
( 7) STATE:         2e 8f 9c 65 a9 fc 20 a3 
( 7) SUBKEY:        70 8a d2 dd b3 c0 
( 8) STATE:         a9 fc 20 a3 30 8b ee 97 
( 8) SUBKEY:        34 f8 22 f0 c6 6d 
( 9) STATE:         30 8b ee 97 10 af 9d 37 
( 9) SUBKEY:        84 bb 44 73 dc cc 
(10) STATE:         10 af 9d 37 6c a6 cb 20 
(10) SUBKEY:        02 76 57 08 b5 bf 
(11) STATE:         6c a6 cb 20 ff 3c 48 5f 
(11) SUBKEY:        6d 55 60 af 7c a5 
(12) STATE:         ff 3c 48 5f 22 a5 96 3b 
(12) SUBKEY:        c2 c1 e9 6a 4b f3 
(13) STATE:         22 a5 96 3b 38 7c cd aa 
(13) SUBKEY:        99 c3 13 97 c9 1f 
(14) STATE:         38 7c cd aa bd 2d d2 ab 
(14) SUBKEY:        25 1b 8b c7 17 d0 
(15) STATE:         bd 2d d2 ab cf 26 b4 72 
(15) SUBKEY:        33 30 c5 d9 a3 6d 
(16) STATE:         cf 26 b4 72 19 ba 92 12 
(16) SUBKEY:        18 1c 5d 75 c6 6d 
FINAL SWAP:         19 ba 92 12 cf 26 b4 72 
INVERSE IP:         c0 b7 a8 d0 5f 3a 82 9c 
ENCRYPT OUTPUT:     c0 b7 a8 d0 5f 3a 82 9c 
[DEBUG] DES DECRYPT
CIPHERTEXT:         c0 b7 a8 d0 5f 3a 82 9c 
KEY:                aa bb 09 18 27 36 cc dd 
IP:                 19 ba 92 12 cf 26 b4 72 
(16) STATE:         cf 26 b4 72 bd 2d d2 ab 
(16) SUBKEY:        18 1c 5d 75 c6 6d 
(15) STATE:         bd 2d d2 ab 38 7c cd aa 
(15) SUBKEY:        33 30 c5 d9 a3 6d 
(14) STATE:         38 7c cd aa 22 a5 96 3b 
(14) SUBKEY:        25 1b 8b c7 17 d0 
(13) STATE:         22 a5 96 3b ff 3c 48 5f 
(13) SUBKEY:        99 c3 13 97 c9 1f 
(12) STATE:         ff 3c 48 5f 6c a6 cb 20 
(12) SUBKEY:        c2 c1 e9 6a 4b f3 
(11) STATE:         6c a6 cb 20 10 af 9d 37 
(11) SUBKEY:        6d 55 60 af 7c a5 
(10) STATE:         10 af 9d 37 30 8b ee 97 
(10) SUBKEY:        02 76 57 08 b5 bf 
( 9) STATE:         30 8b ee 97 a9 fc 20 a3 
( 9) SUBKEY:        84 bb 44 73 dc cc 
( 8) STATE:         a9 fc 20 a3 2e 8f 9c 65 
( 8) SUBKEY:        34 f8 22 f0 c6 6d 
( 7) STATE:         2e 8f 9c 65 a1 5a 4b 87 
( 7) SUBKEY:        70 8a d2 dd b3 c0 
( 6) STATE:         a1 5a 4b 87 23 67 79 c2 
( 6) SUBKEY:        c1 94 8e 87 47 5e 
( 5) STATE:         23 67 79 c2 b8 08 95 91 
( 5) SUBKEY:        69 a6 29 fe c9 13 
( 4) STATE:         b8 08 95 91 4a 12 10 f6 
( 4) SUBKEY:        da 2d 03 2b 6e e3 
( 3) STATE:         4a 12 10 f6 5a 78 e3 94 
( 3) SUBKEY:        06 ed a4 ac f5 b5 
( 2) STATE:         5a 78 e3 94 18 ca 18 ad 
( 2) SUBKEY:        45 68 58 1a bc ce 
( 1) STATE:         18 ca 18 ad 14 a7 d6 78 
( 1) SUBKEY:        19 4c d0 72 de 8c 
FINAL SWAP:         14 a7 d6 78 18 ca 18 ad 
INVERSE IP:         12 34 56 ab cd 13 25 36 
DECRYPT OUTPUT:     12 34 56 ab cd 13 25 36
```

A sample test vector for one (1) round of the DES feistel network:

```
$ ./tracefeistel
INPUT STATE:        14 a7 d6 78 18 ca 18 ad 
INPUT R:            18 ca 18 ad 
INPUT SUBKEY:       19 4c d0 72 de 8c 
E EXPANSION:        8f 16 54 0f 15 5a 
SUBKEY ADDITION:    96 5a 84 7d cb d6 
S-BOX 1:            100101 (3, 2) -> 1000
S-BOX 2:            100101 (3, 2) -> 1010
S-BOX 3:            101010 (2, 5) -> 1111
S-BOX 4:            000100 (0, 2) -> 1110
S-BOX 5:            011111 (1,15) -> 0110
S-BOX 6:            011100 (0,14) -> 0101
S-BOX 7:            101111 (3, 7) -> 0111
S-BOX 8:            010110 (0,11) -> 1110
SUBSTITUTION:       8a fe 65 7e 
PERMUTATION:        4e df 35 ec 
FUNCTION OUT:       4e df 35 ec 
XOR:                5a 78 e3 94 
```

A sample test vector for the DES function:

```
$ ./tracefunc 
INPUT R:            18 ca 18 ad 
INPUT SUBKEY:       19 4c d0 72 de 8c 
E EXPANSION:        8f 16 54 0f 15 5a 
SUBKEY ADDITION:    96 5a 84 7d cb d6 
S-BOX 1:            100101 (3, 2) -> 1000
S-BOX 2:            100101 (3, 2) -> 1010
S-BOX 3:            101010 (2, 5) -> 1111
S-BOX 4:            000100 (0, 2) -> 1110
S-BOX 5:            011111 (1,15) -> 0110
S-BOX 6:            011100 (0,14) -> 0101
S-BOX 7:            101111 (3, 7) -> 0111
S-BOX 8:            010110 (0,11) -> 1110
SUBSTITUTION:       8a fe 65 7e 
PERMUTATION:        4e df 35 ec 
```
