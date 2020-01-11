### Salsa20 Implementation

An implementation of the Salsa20 core and stream cipher, as described by their creator DJB [here](https://cr.yp.to/salsa20.html) and [here](https://cr.yp.to/snuffle.html).

#### Usage

Among the programs included in this repository is a command line interface to the Salsa20 stream cipher. The program takes a 32-byte key and a 16-byte nonce and applies the Salsa20 stream cipher to input read from `stdin`, writing the result to `stdout`. Example usage is shown below. 

```
$ KEY=$(python -c 'print "A"*32')
$ echo $KEY
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
$ NONCE=$(python -c 'print "B"*16')
$ echo $NONCE
BBBBBBBBBBBBBBBB
$ echo 11223344 | ./salsa20 $KEY $NONCE > out.txt
$ cat out.txt | hexdump
0000000 fc 3e 41 bf 3e 3d 15 d2 b0
0000009
$ cat out.txt | ./salsa20 $KEY $NONCE
11223344
```

#### Build 

To build a test program:

```
make test
```

To build a test program with debugging output:

```
make debug
```

To build the hash function test program:

```
make hash
```

To build the command line tool:

```
make cli
```

To build the library for export:

```
make lib
```

To clean up after yourself when you're done:

```
make clean
```

#### Correctness: Salsa20 Hash

Compare the following output with that provided in the Salsa20 [specification](https://cr.yp.to/snuffle/spec.pdf).

```
vector 1 in:
 211 159  13 115  76  55  82 183   3 117 222  37 191 187 234 136
  49 237 179  48   1 106 178 219 175 199 166  48  86  16 179 207
  31 240  32  63  15  83  93 161 116 147  48 113 238  55 204  36
  79 201 235  79   3  81 156  47 203  26 244 243  88 118 104  54
vector 1 salsa20 hash digest:
 109  42 178 168 156 240 248 238 168 196 190 203  26 110 170 154
  29  29 150  26 150  30 235 249 190 163 251  48  69 144  51  57
 118  40 152 157 180  57  27  94 107  42 236  35  27 111 114 114
 219 236 232 135 111 155 110  18  24 232  95 158 179  19  48 202
vector 2 in:
  88 118 104  54  79 201 235  79   3  81 156  47 203  26 244 243
 191 187 234 136 211 159  13 115  76  55  82 183   3 117 222  37
  86  16 179 207  49 237 179  48   1 106 178 219 175 199 166  48
 238  55 204  36  31 240  32  63  15  83  93 161 116 147  48 113
vector 2 salsa20 hash digest:
 179  19  48 202 219 236 232 135 111 155 110  18  24 232  95 158
  26 110 170 154 109  42 178 168 156 240 248 238 168 196 190 203
  69 144  51  57  29  29 150  26 150  30 235 249 190 163 251  48
  27 111 114 114 118  40 152 157 180  57  27  94 107  42 236  35
```

#### Correctness: Internal State Evolution

Compare the following output to Jean-Philippe Aumasson's [coverage](https://seriouscrypto.com/) of the Salsa20 core function. 

```
key = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
}
nonce = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF 
}

init state for ctr  = 0               init state for ctr  = 1
61707865 00000000 00000000 00000000   61707865 00000000 00000000 00000000 
00000000 3320646e ffffffff ffffffff   00000000 3320646e ffffffff ffffffff 
00000000 00000000 79622d32 00000000   00000001 00000000 79622d32 00000000 
00000000 00000000 00000000 6b206574   00000000 00000000 00000000 6b206574 

final state for ctr = 0               final state for ctr = 1
e98680bc f730ba7a 38663ce0 5f376d93   1ba4d492 c14270c3 9fb05306 ff808c64
85683b75 a56ca873 26501592 64144b6d   b49a4100 f5d8fbbd 614234a0 e20663d1
6dcb46fd 58178f93 8cf54cfe cfdc27d7   12e1e116 6a61bc8f 86f01bcb 2efead4a 
68bbe09e 17b403a1 38aa1f27 54323fe0   77775a13 d17b99d5 eb773f5b 2c3a5e7d 
```

#### Correctness: Stream Cipher Operations 

Just trust me on this one; XOR works. 

```
$ ./test
plaintext in:
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
ciphertext:
21 e8 d4 79 3e ef 56 80 68 a5 cc 83 5f b0 d9 a0 
75 2a 4a b6 a5 59 eb af 19 8c fa 9d a0 96 fa 9b 
fd 57 e9 5e d7 da 71 2f b8 e3 fd bd 1b fa 32 30 
9e f1 99 5b e5 56 d2 60 af 86 00 83 98 78 bc 40 
plaintext out:
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
00 11 22 33 44 55 66 77 88 99 aa bb cc dd ee ff 
```
