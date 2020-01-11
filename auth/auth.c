// auth.c 
// Cryptographic message authentication primitives. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "auth.h"
#include "../aes/cipher/aes.h"
#include "../aes/cipher/const.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

static uint8_t CMAC_CONST_Z[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static uint8_t CMAC_CONST_R[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x87
};

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void cmac_keygen(uint8_t *k1, uint8_t *k2, uint8_t *key);
static void cmac_padding(uint8_t *dst, uint8_t *src, size_t nbytes);

static void bcpy(uint8_t *dst, uint8_t *src, size_t size);
static void lshift(uint8_t *block, size_t bsize);
static int  msb(uint8_t *block);
static void xor(uint8_t *r, uint8_t *a, uint8_t *b);
static void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
	Exported Functions
	See module header file (auth.h) for detailed function comments.
*/

// compute CMAC MAC
int auth_cmac_gen(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *key) {
	// temporary buffers for subkeys 
	uint8_t k1[AES_128_KEY_SIZE];
	uint8_t k2[AES_128_KEY_SIZE];

	// generate subkeys from primary key
	cmac_keygen(k1, k2, key);

	size_t overflow  = mlen % AES_BLOCK_SIZE;  						  // bytes past end of nearest full block        
	size_t remainder = (AES_BLOCK_SIZE - overflow) % AES_BLOCK_SIZE;  // number of bytes short of full block 
	size_t nblocks   = ((mlen + remainder) / AES_BLOCK_SIZE);         // total number of blocks in message (ceiling)

	// compute the special 'mlast' block
	uint8_t mlast[AES_BLOCK_SIZE];
	if (mlen == 0) {
		// special case: zero-length message
		cmac_padding(mlast, msg, AES_BLOCK_SIZE);
		// mlast <- padding(M_n)       
		xor(mlast, mlast, k2); 
	} else if (remainder > 0) {
		// pad M out to multiple of block size
		cmac_padding(mlast, msg+(AES_BLOCK_SIZE*(nblocks-1)), remainder);   
		// mlast <- padding(M_n)       
		xor(mlast, mlast, k2);  							           
	} else {
		// final block is complete, no padding necessary
		bcpy(mlast, msg+(AES_BLOCK_SIZE*(nblocks-1)), AES_BLOCK_SIZE);
		 // mlast <- M_n XOR k1
		xor(mlast, msg+(AES_BLOCK_SIZE*(nblocks-1)), k1);            
	}

	// temporary buffers for MAC calculation
	uint8_t X[AES_BLOCK_SIZE];
	uint8_t Y[AES_BLOCK_SIZE];

	// X <- 0
	bcpy(X, CMAC_CONST_Z, AES_BLOCK_SIZE);

	// process M_1 .. M_{n-1} via CBC encryption
	for (size_t i = 0; (mlen > 0) && (i < (nblocks - 1)); i++) {
		xor(Y, X, msg+(AES_BLOCK_SIZE*i));   // Y <- X XOR M_i
		aes_128_encrypt(X, Y, key);          // X <- AES(key, Y);
	}

	xor(Y, mlast, X);              // Y <- mlast XOR X
	aes_128_encrypt(tag, Y, key);  // tag <- AES(key, Y)

	return 0;
}

// verify CMAC MAC
bool auth_cmac_ver(uint8_t *msg, size_t mlen, uint8_t *key, uint8_t *tag) {
	// generate a new tag
	uint8_t newtag[AES_BLOCK_SIZE];
	auth_cmac_gen(newtag, msg, mlen, key);

	uint8_t res = 0;
	for (size_t i = 0; i < AES_BLOCK_SIZE; i++)
		res |= (tag[i] ^ newtag[i]);
	return res == 0; 
}

// compute encrypted CBC MAC
int auth_ecbc(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *k1, uint8_t *k2) {
	if (!tag || !msg || !k1 || !k2)
		return 1;

	// Q: use a temporary buffer here?
	// I prefer not to touch the output buffer until result is finalized, 
	// but I don't know if I can properly defend this predilection
	uint8_t tmp[AES_BLOCK_SIZE];

	// compute raw CBC tag
	if (auth_rawcbc(tmp, msg, mlen, k1) != 0) 
		return 1;

	// compute final encryption: 
	// tag <- AES(k2, tmp)
	aes_128_encrypt(tag, tmp, k2);

	return 0;
}

// compute raw CBC MAC
int auth_rawcbc(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *key) {
	if (!tag || !msg || !key)
		return 1;

	// caller deals with padding: 
	// rawcbc MAC and ECBC MAC handle only fixed-length messages
	// (where fixed-length = multiple of underlying block size)
	if (mlen % AES_BLOCK_SIZE != 0)
		return 1;

	size_t nblocks = mlen / AES_BLOCK_SIZE;

	// the encryption operation buffer
	// initialization to 0 -> 0 initialization vector
	uint8_t buf[16] = { 0 };  

	for (size_t block = 0; block < nblocks; block++) {
		// buf <- buf XOR msg[block]
		xor(buf, buf, msg+(block*AES_BLOCK_SIZE));
		// buf <- AES(key, buf)
		aes_128_encrypt(buf, buf, key);
	}

	// final buffer content is tag value
	memcpy(tag, buf, AES_BLOCK_SIZE);

	return 0; 
}

/* ----------------------------------------------------------------------------
	Local Functions - CMAC
*/

// CMAC subkey generation algorithm
static void cmac_keygen(uint8_t *k1, uint8_t *k2, uint8_t *key) {
	uint8_t l[AES_BLOCK_SIZE];

	// encrypt the constant 0 block under primary key
	aes_128_encrypt(l, CMAC_CONST_Z, key);

	// derive subkey k1
	bcpy(k1, l, AES_BLOCK_SIZE);
	lshift(k1, AES_BLOCK_SIZE);
	if (msb(l) == 1) 
		xor(k1, k1, CMAC_CONST_R);  // k1 <- k1 XOR const_r

	// derive subkey k2
	bcpy(k2, k1, AES_BLOCK_SIZE);
	lshift(k2, AES_BLOCK_SIZE);
	if (msb(k1) == 1)
		xor(k2, k2, CMAC_CONST_R);  // k2 <- k2 XOR const_r
}

// pad out the final <nbytes> bytes of block: dst <- pad(src)
static void cmac_padding(uint8_t *dst, uint8_t *src, size_t nbytes) {
	size_t idx = 0; 
	for (;idx < AES_BLOCK_SIZE - nbytes; idx++)
		dst[idx] = src[idx];
	dst[idx++] = 0x80;
	while (idx < AES_BLOCK_SIZE)
		dst[idx++] = 0x00;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// block copy: dst <- src 
static void bcpy(uint8_t *dst, uint8_t *src, size_t size) {
	for (size_t i = 0; i < size; i++) 
		dst[i] = src[i];
}

// bitwise left shift arbitrary byte vector by 1 bit
static void lshift(uint8_t *block, size_t bsize) {
	for (size_t i = 0; i < bsize - 1; i++) 
		block[i] = (block[i] << 1) | (block[i+1] >> 7);
	block[bsize - 1] <<= 1;
}

// return MSB of arbitrary byte vector
static int msb(uint8_t *block) {
	return (block[0] >> 7); 
}

// block r <- block a ^ block b
static void xor(uint8_t *r, uint8_t *a, uint8_t *b) {
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
		r[i] = a[i] ^ b[i];
}

// print hexadecimal-formatted bytes to stdout
static void hexdump(uint8_t *bytes, size_t len) {
	for (size_t i = 0; i < len; i++) 
		printf("%02x ", bytes[i]);
	putchar('\n');
}
