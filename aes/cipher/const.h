// const.h
// Constant values for AES encryption standard implementation.
//
// See https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf.  

#ifndef __AES_CONST_H
#define __AES_CONST_H

// algorithm block size, in bytes 
#define AES_BLOCK_SIZE 16  

// number of 32-bit words in block (Nb)
#define AES_BLOCK_WORDS 4

// number of 32-bit words comprising the cipher key (Nk)
#define AES_128_KEY_WORDS 4 
#define AES_192_KEY_WORDS 6
#define AES_256_KEY_WORDS 8

// number of bytes comprising the cipher key 
// (useful for external libs, not used in cipher)
#define AES_128_KEY_SIZE 16
#define AES_192_KEY_SIZE 24
#define AES_256_KEY_SIZE 32

// number of cipher rounds (Nr)
#define AES_128_NROUNDS 10
#define AES_192_NROUNDS 12
#define AES_256_NROUNDS 14

// m(x) = x^8 + x^4 + x^3 + x + 1
// bit vector representation of AES irreducible polynomial
#define AES_POLY 0x1B

#endif // __AES_CONST_H
