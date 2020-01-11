### Chacha20 Implementation

An implementation of the chacha20 stream cipher and related primitives, as described in [RFC 7539](https://tools.ietf.org/html/rfc7539). 

#### Usage 

Among the programs included in this repository is a command line interface to the Chacha20 stream cipher. The program takes a 32-byte key and a 12-byte nonce and applies the Chacha20 stream cipher to input read from `stdin`, writing the result to `stdout`. Example usage is shown below. 

```
$ KEY=$(python -c 'print "A"*32')
$ NONCE=$(python -c 'print "B"*12')
$ echo $KEY
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
$ echo $NONCE
BBBBBBBBBBBB
$ echo 11223344 | ./chacha20 $KEY $NONCE > out.txt
$ cat out.txt | hexdump
0000000 60 cc fb a2 6a f5 c8 80 f1                     
0000009
$ cat out.txt | ./chacha20 $KEY $NONCE
11223344
```

#### Build

To build the test program for the core function:

```
make test_core
```

To build the test program for the stream cipher algorithm:

```
make test_cipher
```

To build the module for export:

```
make lib
```

To clean up after yourself:

```
make clean
```

#### Correctness: Core Function

Compare the following output to the test vector provided in section 2.3.2 of the [RFC](https://tools.ietf.org/html/rfc7539#section-2.1). 

```
$ ./test_core 
[DEBUG] input key:
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
[DEBUG] input nonce:
00 00 00 09 00 00 00 4a 00 00 00 00 
[DEBUG] input block counter: 00000001
[DEBUG] initial state (block counter 1):
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000001 09000000 4a000000 00000000 
[DEBUG] after 20 rounds:
837778ab e238d763 a67ae21e 5950bb2f 
c4f2d0c7 fc62bb2f 8fa018fc 3f5ec7b7 
335271c2 f29489f3 eabda8fc 82e46ebd 
d19c12b4 b04e16de 9e83d0cb 4e3c50a2 
[DEBUG] after addition with original state:
e4e7f110 15593bd1 1fdd0f50 c47120a3 
c7f4d1c7 0368c033 9aaa2204 4e6cd4c3 
466482d2 09aa9f07 05d7c214 a2028bd9 
d19c12b5 b94e16de e883d0cb 4e3c50a2 
[DEBUG] serialized output block:
10 f1 e7 e4 d1 3b 59 15 50 0f dd 1f a3 20 71 c4 
c7 d1 f4 c7 33 c0 68 03 04 22 aa 9a c3 d4 6c 4e 
d2 82 64 46 07 9f aa 09 14 c2 d7 05 d9 8b 02 a2 
b5 12 9c d1 de 16 4e b9 cb d0 83 e8 a2 50 3c 4e
```

#### Correctness: Stream Cipher Algorithm

Compare the following output to the test vector provided in section 2.4.2 of the [RFC](https://tools.ietf.org/html/rfc7539#section-2.1).

```
$ ./test_cipher 
[DEBUG] input key:
00 01 02 03 04 05 06 07 08 09 0a 0b 0c 0d 0e 0f 10 11 12 13 14 15 16 17 18 19 1a 1b 1c 1d 1e 1f 
[DEBUG] input nonce:
00 00 00 00 00 00 00 4a 00 00 00 00 
[DEBUG] input block counter: 00000001
[DEBUG] initial state (block counter 1):
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000001 00000000 4a000000 00000000 
[DEBUG] after 20 rounds:
91e0d6bd aeb8b6d2 f5c5b0fd 81fcfe44 
7f1d128c db002739 e1c04676 69c1e692 
8ff82a7a 7af44b5e b25a609d 15750ed1 
40ba4c78 cd343ec6 022c21ea b7417df0 
[DEBUG] after addition with original state:
f3514f22 e1d91b40 6f27de2f ed1d63b8 
821f138c e2062c3d ecca4f7e 78cff39e 
a30a3b8a 920a6072 cd7479b5 34932bed 
40ba4c79 cd343ec6 4c2c21ea b7417df0 
[DEBUG] initial state (block counter 2):
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000002 00000000 4a000000 00000000 
[DEBUG] after 20 rounds:
3e042e04 0deefed1 af9c9cf0 13a3e878 
6a32d326 6c86b46c 2fbbe0eb 364affb8 
c75c7a29 72166e06 b2d04ea9 0c600074 
037463f1 a11a2073 9ebcfb88 edc49139 
[DEBUG] after addition with original state:
9f74a669 410f633f 28feca22 7ec44dec 
6d34d426 738cb970 3ac5e9f3 45590cc4 
da6e8b39 892c831a cdea67c1 2b7e1d90 
037463f3 a11a2073 e8bcfb88 edc49139 
[DEBUG] initial state (block counter 1):
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000001 00000000 4a000000 00000000 
[DEBUG] after 20 rounds:
91e0d6bd aeb8b6d2 f5c5b0fd 81fcfe44 
7f1d128c db002739 e1c04676 69c1e692 
8ff82a7a 7af44b5e b25a609d 15750ed1 
40ba4c78 cd343ec6 022c21ea b7417df0 
[DEBUG] after addition with original state:
f3514f22 e1d91b40 6f27de2f ed1d63b8 
821f138c e2062c3d ecca4f7e 78cff39e 
a30a3b8a 920a6072 cd7479b5 34932bed 
40ba4c79 cd343ec6 4c2c21ea b7417df0 
[DEBUG] initial state (block counter 2):
61707865 3320646e 79622d32 6b206574 
03020100 07060504 0b0a0908 0f0e0d0c 
13121110 17161514 1b1a1918 1f1e1d1c 
00000002 00000000 4a000000 00000000 
[DEBUG] after 20 rounds:
3e042e04 0deefed1 af9c9cf0 13a3e878 
6a32d326 6c86b46c 2fbbe0eb 364affb8 
c75c7a29 72166e06 b2d04ea9 0c600074 
037463f1 a11a2073 9ebcfb88 edc49139 
[DEBUG] after addition with original state:
9f74a669 410f633f 28feca22 7ec44dec 
6d34d426 738cb970 3ac5e9f3 45590cc4 
da6e8b39 892c831a cdea67c1 2b7e1d90 
037463f3 a11a2073 e8bcfb88 edc49139 
[DEBUG] plaintext:
4c 61 64 69 65 73 20 61 6e 64 20 47 65 6e 74 6c 
65 6d 65 6e 20 6f 66 20 74 68 65 20 63 6c 61 73 
73 20 6f 66 20 27 39 39 3a 20 49 66 20 49 20 63 
6f 75 6c 64 20 6f 66 66 65 72 20 79 6f 75 20 6f 
6e 6c 79 20 6f 6e 65 20 74 69 70 20 66 6f 72 20 
74 68 65 20 66 75 74 75 72 65 2c 20 73 75 6e 73 
63 72 65 65 6e 20 77 6f 75 6c 64 20 62 65 20 69 
74 2e 
[DEBUG] ciphertext:
6e 2e 35 9a 25 68 f9 80 41 ba 07 28 dd 0d 69 81 
e9 7e 7a ec 1d 43 60 c2 0a 27 af cc fd 9f ae 0b 
f9 1b 65 c5 52 47 33 ab 8f 59 3d ab cd 62 b3 57 
16 39 d6 24 e6 51 52 ab 8f 53 0c 35 9f 08 61 d8 
07 ca 0d bf 50 0d 6a 61 56 a3 8e 08 8a 22 b6 5e 
52 bc 51 4d 16 cc f8 06 81 8c e9 1a b7 79 37 36 
5a f9 0b bf 74 a3 5b e6 b4 0b 8e ed f2 78 5e 42 
87 4d 
[DEBUG] newtext:
4c 61 64 69 65 73 20 61 6e 64 20 47 65 6e 74 6c 
65 6d 65 6e 20 6f 66 20 74 68 65 20 63 6c 61 73 
73 20 6f 66 20 27 39 39 3a 20 49 66 20 49 20 63 
6f 75 6c 64 20 6f 66 66 65 72 20 79 6f 75 20 6f 
6e 6c 79 20 6f 6e 65 20 74 69 70 20 66 6f 72 20 
74 68 65 20 66 75 74 75 72 65 2c 20 73 75 6e 73 
63 72 65 65 6e 20 77 6f 75 6c 64 20 62 65 20 69 
74 2e 
```