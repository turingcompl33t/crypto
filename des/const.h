// const.h
// DES constant values. 

#ifndef __DES_CONST_H
#define __DES_CONST_H

// number of cipher rounds 
#define DES_NROUNDS 16

// cipher block size, in bytes 
#define DES_BLOCK_SIZE_BYTES 8
// cipher block size, in bits
#define DES_BLOCK_SIZE_BITS  64

// effective cipher key length, in bits
#define DES_EFFECTIVE_KEYLEN_BITS 56
// effective cipher key length, bytes
#define DES_EFFECTIVE_KEYLEN_BYTES 7

// cipher round subkey length
#define DES_SUBKEY_SIZE_BYTES 6
#define DES_SUBKEY_SIZE_BITS  48

#endif // __DES_CONST_H
