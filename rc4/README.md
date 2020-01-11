### RC4 Implementation

This probably isn't dangerous at all. 

### Correctness

Compare the following output from the `vectors` program with the RC4 keystream test vectors provided in [RFC 6229](https://tools.ietf.org/html/rfc6229). 

```Bash
$ ./vectors 
Key len: 40 bits
Key    : 0x0102030405
DEC    0 HEX    0: b2 39 63 05 f0 3d c0 27 cc c3 52 4a 0a 11 18 a8 
DEC   16 HEX   10: 69 82 94 4f 18 fc 82 d5 89 c4 03 a4 7a 0d 09 19 
DEC  240 HEX   f0: 28 cb 11 32 c9 6c e2 86 42 1d ca ad b8 b6 9e ae 
DEC  256 HEX  100: 1c fc f6 2b 03 ed db 64 1d 77 df cf 7f 8d 8c 93 
DEC  496 HEX  1f0: 42 b7 d0 cd d9 18 a8 a3 3d d5 17 81 c8 1f 40 41 
DEC  512 HEX  200: 64 59 84 44 32 a7 da 92 3c fb 3e b4 98 06 61 f6 
DEC  752 HEX  2f0: ec 10 32 7b de 2b ee fd 18 f9 27 76 80 45 7e 22 
DEC  768 HEX  300: eb 62 63 8d 4f 0b a1 fe 9f ca 20 e0 5b f8 ff 2b 
DEC 1008 HEX  3f0: 45 12 90 48 e6 a0 ed 0b 56 b4 90 33 8f 07 8d a5 
DEC 1024 HEX  400: 30 ab bc c7 c2 0b 01 60 9f 23 ee 2d 5f 6b b7 df 
DEC 1520 HEX  5f0: 32 94 f7 44 d8 f9 79 05 07 e7 0f 62 e5 bb ce ea 
DEC 1536 HEX  600: d8 72 9d b4 18 82 25 9b ee 4f 82 53 25 f5 a1 30 
DEC 2032 HEX  7f0: 1e b1 4a 0c 13 b3 bf 47 fa 2a 0b a9 3a d4 5b 8b 
DEC 2048 HEX  800: cc 58 2f 8b a9 f2 65 e2 b1 be 91 12 e9 75 d2 d7 
DEC 3056 HEX  bf0: f2 e3 0f 9b d1 02 ec bf 75 aa ad e9 bc 35 c4 3c 
DEC 3072 HEX  c00: ec 0e 11 c4 79 dc 32 9d c8 da 79 68 fe 96 56 81 
DEC 4080 HEX  ff0: 06 83 26 a2 11 84 16 d2 1f 9d 04 b2 cd 1c a0 50 
DEC 4096 HEX 1000: ff 25 b5 89 95 99 67 07 e5 1f bd f0 8b 34 d8 75 

Key len: 56 bits
Key    : 0x01020304050607
DEC    0 HEX    0: 29 3f 02 d4 7f 37 c9 b6 33 f2 af 52 85 fe b4 6b 
DEC   16 HEX   10: e6 20 f1 39 0d 19 bd 84 e2 e0 fd 75 20 31 af c1 
DEC  240 HEX   f0: 91 4f 02 53 1c 92 18 81 0d f6 0f 67 e3 38 15 4c 
DEC  256 HEX  100: d0 fd b5 83 07 3c e8 5a b8 39 17 74 0e c0 11 d5 
DEC  496 HEX  1f0: 75 f8 14 11 e8 71 cf fa 70 b9 0c 74 c5 92 e4 54 
DEC  512 HEX  200: 0b b8 72 02 93 8d ad 60 9e 87 a5 a1 b0 79 e5 e4 
DEC  752 HEX  2f0: c2 91 12 46 b6 12 e7 e7 b9 03 df ed a1 da d8 66 
DEC  768 HEX  300: 32 82 8f 91 50 2b 62 91 36 8d e8 08 1d e3 6f c2 
DEC 1008 HEX  3f0: f3 b9 a7 e3 b2 97 bf 9a d8 04 51 2f 90 63 ef f1 
DEC 1024 HEX  400: 8e cb 67 a9 ba 1f 55 a5 a0 67 e2 b0 26 a3 67 6f 
DEC 1520 HEX  5f0: d2 aa 90 2b d4 2d 0d 7c fd 34 0c d4 58 10 52 9f 
DEC 1536 HEX  600: 78 b2 72 c9 6e 42 ea b4 c6 0b d9 14 e3 9d 06 e3 
DEC 2032 HEX  7f0: f4 33 2f d3 1a 07 93 96 ee 3c ee 3f 2a 4f f0 49 
DEC 2048 HEX  800: 05 45 97 81 d4 1f da 7f 30 c1 be 7e 12 46 c6 23 
DEC 3056 HEX  bf0: ad fd 38 68 b8 e5 14 85 d5 e6 10 01 7e 3d d6 09 
DEC 3072 HEX  c00: ad 26 58 1c 0c 5b e4 5f 4c ea 01 db 2f 38 05 d5 
DEC 4080 HEX  ff0: f3 17 2c ef fc 3b 3d 99 7c 85 cc d5 af 1a 95 0c 
DEC 4096 HEX 1000: e7 4b 0b 97 31 22 7f d3 7c 0e c0 8a 47 dd d8 b8 

Key len: 64 bits
Key    : 0x0102030405060708
DEC    0 HEX    0: 97 ab 8a 1b f0 af b9 61 32 f2 f6 72 58 da 15 a8 
DEC   16 HEX   10: 82 63 ef db 45 c4 a1 86 84 ef 87 e6 b1 9e 5b 09 
DEC  240 HEX   f0: 96 36 eb c9 84 19 26 f4 f7 d1 f3 62 bd df 6e 18 
DEC  256 HEX  100: d0 a9 90 ff 2c 05 fe f5 b9 03 73 c9 ff 4b 87 0a 
DEC  496 HEX  1f0: 73 23 9f 1d b7 f4 1d 80 b6 43 c0 c5 25 18 ec 63 
DEC  512 HEX  200: 16 3b 31 99 23 a6 bd b4 52 7c 62 61 26 70 3c 0f 
DEC  752 HEX  2f0: 49 d6 c8 af 0f 97 14 4a 87 df 21 d9 14 72 f9 66 
DEC  768 HEX  300: 44 17 3a 10 3b 66 16 c5 d5 ad 1c ee 40 c8 63 d0 
DEC 1008 HEX  3f0: 27 3c 9c 4b 27 f3 22 e4 e7 16 ef 53 a4 7d e7 a4 
DEC 1024 HEX  400: c6 d0 e7 b2 26 25 9f a9 02 34 90 b2 61 67 ad 1d 
DEC 1520 HEX  5f0: 1f e8 98 67 13 f0 7c 3d 9a e1 c1 63 ff 8c f9 d3 
DEC 1536 HEX  600: 83 69 e1 a9 65 61 0b e8 87 fb d0 c7 91 62 aa fb 
DEC 2032 HEX  7f0: 0a 01 27 ab b4 44 84 b9 fb ef 5a bc ae 1b 57 9f 
DEC 2048 HEX  800: c2 cd ad c6 40 2e 8e e8 66 e1 f3 7b db 47 e4 2c 
DEC 3056 HEX  bf0: 26 b5 1e a3 7d f8 e1 d6 f7 6f c3 b6 6a 74 29 b3 
DEC 3072 HEX  c00: bc 76 83 20 5d 4f 44 3d c1 f2 9d da 33 15 c8 7b 
DEC 4080 HEX  ff0: d5 fa 5a 34 69 d2 9a aa f8 3d 23 58 9d b8 c8 5b 
DEC 4096 HEX 1000: 3f b4 6e 2c 8f 0f 06 8e dc e8 cd cd 7d fc 58 62 

Key len: 128 bits
Key    : 0x0102030405060708090a0b0c0d0e0f10
DEC    0 HEX    0: 9a c7 cc 9a 60 9d 1e f7 b2 93 28 99 cd e4 1b 97 
DEC   16 HEX   10: 52 48 c4 95 90 14 12 6a 6e 8a 84 f1 1d 1a 9e 1c 
DEC  240 HEX   f0: 06 59 02 e4 b6 20 f6 cc 36 c8 58 9f 66 43 2f 2b 
DEC  256 HEX  100: d3 9d 56 6b c6 bc e3 01 07 68 15 15 49 f3 87 3f 
DEC  496 HEX  1f0: b6 d1 e6 c4 a5 e4 77 1c ad 79 53 8d f2 95 fb 11 
DEC  512 HEX  200: c6 8c 1d 5c 55 9a 97 41 23 df 1d bc 52 a4 3b 89 
DEC  752 HEX  2f0: c5 ec f8 8d e8 97 fd 57 fe d3 01 70 1b 82 a2 59 
DEC  768 HEX  300: ec cb e1 3d e1 fc c9 1c 11 a0 b2 6c 0b c8 fa 4d 
DEC 1008 HEX  3f0: e7 a7 25 74 f8 78 2a e2 6a ab cf 9e bc d6 60 65 
DEC 1024 HEX  400: bd f0 32 4e 60 83 dc c6 d3 ce dd 3c a8 c5 3c 16 
DEC 1520 HEX  5f0: b4 01 10 c4 19 0b 56 22 a9 61 16 b0 01 7e d2 97 
DEC 1536 HEX  600: ff a0 b5 14 64 7e c0 4f 63 06 b8 92 ae 66 11 81 
DEC 2032 HEX  7f0: d0 3d 1b c0 3c d3 3d 70 df f9 fa 5d 71 96 3e bd 
DEC 2048 HEX  800: 8a 44 12 64 11 ea a7 8b d5 1e 8d 87 a8 87 9b f5 
DEC 3056 HEX  bf0: fa be b7 60 28 ad e2 d0 e4 87 22 e4 6c 46 15 a3 
DEC 3072 HEX  c00: c0 5d 88 ab d5 03 57 f9 35 a6 3c 59 ee 53 76 23 
DEC 4080 HEX  ff0: ff 38 26 5c 16 42 c1 ab e8 d3 c2 fe 5e 57 2b f8 
DEC 4096 HEX 1000: a3 6a 4c 30 1a e8 ac 13 61 0c cb c1 22 56 ca cc 

Key len: 192 bits
Key    : 0x0102030405060708090a0b0c0d0e0f101112131415161718
DEC    0 HEX    0: 05 95 e5 7f e5 f0 bb 3c 70 6e da c8 a4 b2 db 11 
DEC   16 HEX   10: df de 31 34 4a 1a f7 69 c7 4f 07 0a ee 9e 23 26 
DEC  240 HEX   f0: b0 6b 9b 1e 19 5d 13 d8 f4 a7 99 5c 45 53 ac 05 
DEC  256 HEX  100: 6b d2 37 8e c3 41 c9 a4 2f 37 ba 79 f8 8a 32 ff 
DEC  496 HEX  1f0: e7 0b ce 1d f7 64 5a db 5d 2c 41 30 21 5c 35 22 
DEC  512 HEX  200: 9a 57 30 c7 fc b4 c9 af 51 ff da 89 c7 f1 ad 22 
DEC  752 HEX  2f0: 04 85 05 5f d4 f6 f0 d9 63 ef 5a b9 a5 47 69 82 
DEC  768 HEX  300: 59 1f c6 6b cd a1 0e 45 2b 03 d4 55 1f 6b 62 ac 
DEC 1008 HEX  3f0: 27 53 cc 83 98 8a fa 3e 16 88 a1 d3 b4 2c 9a 02 
DEC 1024 HEX  400: 93 61 0d 52 3d 1d 3f 00 62 b3 c2 a3 bb c7 c7 f0 
DEC 1520 HEX  5f0: 96 c2 48 61 0a ad ed fe af 89 78 c0 3d e8 20 5a 
DEC 1536 HEX  600: 0e 31 7b 3d 1c 73 b9 e9 a4 68 8f 29 6d 13 3a 19 
DEC 2032 HEX  7f0: bd f0 e6 c3 cc a5 b5 b9 d5 33 b6 9c 56 ad a1 20 
DEC 2048 HEX  800: 88 a2 18 b6 e2 ec e1 e6 24 6d 44 c7 59 d1 9b 10 
DEC 3056 HEX  bf0: 68 66 39 7e 95 c1 40 53 4f 94 26 34 21 00 6e 40 
DEC 3072 HEX  c00: 32 cb 0a 1e 95 42 c6 b3 b8 b3 98 ab c3 b0 f1 d5 
DEC 4080 HEX  ff0: 29 a0 b8 ae d5 4a 13 23 24 c6 2e 42 3f 54 b4 c8 
DEC 4096 HEX 1000: 3c b0 f3 b5 02 0a 98 b8 2a f9 fe 15 44 84 a1 68 

Key len: 256 bits
Key    : 0x0102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f20
DEC    0 HEX    0: ea a6 bd 25 88 0b f9 3d 3f 5d 1e 4c a2 61 1d 91 
DEC   16 HEX   10: cf a4 5c 9f 7e 71 4b 54 bd fa 80 02 7c b1 43 80 
DEC  240 HEX   f0: 11 4a e3 44 de d7 1b 35 f2 e6 0f eb ad 72 7f d8 
DEC  256 HEX  100: 02 e1 e7 05 6b 0f 62 39 00 49 64 22 94 3e 97 b6 
DEC  496 HEX  1f0: 91 cb 93 c7 87 96 4e 10 d9 52 7d 99 9c 6f 93 6b 
DEC  512 HEX  200: 49 b1 8b 42 f8 e8 36 7c be b5 ef 10 4b a1 c7 cd 
DEC  752 HEX  2f0: 87 08 4b 3b a7 00 ba de 95 56 10 67 27 45 b3 74 
DEC  768 HEX  300: e7 a7 b9 e9 ec 54 0d 5f f4 3b db 12 79 2d 1b 35 
DEC 1008 HEX  3f0: c7 99 b5 96 73 8f 6b 01 8c 76 c7 4b 17 59 bd 90 
DEC 1024 HEX  400: 7f ec 5b fd 9f 9b 89 ce 65 48 30 90 92 d7 e9 58 
DEC 1520 HEX  5f0: 40 f2 50 b2 6d 1f 09 6a 4a fd 4c 34 0a 58 88 15 
DEC 1536 HEX  600: 3e 34 13 5c 79 db 01 02 00 76 76 51 cf 26 30 73 
DEC 2032 HEX  7f0: f6 56 ab cc f8 8d d8 27 02 7b 2c e9 17 d4 64 ec 
DEC 2048 HEX  800: 18 b6 25 03 bf bc 07 7f ba bb 98 f2 0d 98 ab 34 
DEC 3056 HEX  bf0: 8a ed 95 ee 5b 0d cb fb ef 4e b2 1d 3a 3f 52 f9 
DEC 3072 HEX  c00: 62 5a 1a b0 0e e3 9a 53 27 34 6b dd b0 1a 9c 18 
DEC 4080 HEX  ff0: a1 3a 7c 79 c7 e1 19 b5 ab 02 96 ab 28 c3 00 b9 
DEC 4096 HEX 1000: f3 e4 c0 a2 e0 2d 1d 01 f7 f0 a7 46 18 af 2b 48 
```
