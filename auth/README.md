### Cryptographic Message Authentication

An implementation of various cryptographic primitives for message authentication. 

Implementations derived from the following specifications:

- CMAC message authentication code: as specified by [RFC 4493](https://tools.ietf.org/html/rfc4493)

### Correctness

To verify the correctness of the implementation of the CMAC message authentication code, comparing the following output to the test vectors provided in [RFC 4493](https://tools.ietf.org/html/rfc4493). 

```Bash
$ ./test 
Example 1: len = 0
KEY:
2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c 
M:
<empty string>
CMAC TAG:
bb 1d 69 29 e9 59 37 28 7f a3 7d 12 9b 75 67 46 

Example 2: len = 16
KEY:
2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c 
M:
6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a 
CMAC TAG:
07 0a 16 b4 6b 4d 41 44 f7 9b dd 9d d0 4a 28 7c 

Example 3: len = 40
KEY:
2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c 
M:
6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a 
ae 2d 8a 57 1e 03 ac 9c 9e b7 6f ac 45 af 8e 51 
30 c8 1c 46 a3 5c e4 11 
CMAC TAG:
df a6 67 47 de 9a e6 30 30 ca 32 61 14 97 c8 27 

Example 4: len = 64
KEY:
2b 7e 15 16 28 ae d2 a6 ab f7 15 88 09 cf 4f 3c 
M:
6b c1 be e2 2e 40 9f 96 e9 3d 7e 11 73 93 17 2a 
ae 2d 8a 57 1e 03 ac 9c 9e b7 6f ac 45 af 8e 51 
30 c8 1c 46 a3 5c e4 11 e5 fb c1 19 1a 0a 52 ef 
f6 9f 24 45 df 4f 9b 17 ad 2b 41 7b e6 6c 37 10 
CMAC TAG:
51 f0 be bf 7e 3b 9d 92 fc 49 74 17 79 36 3c fe 
```
