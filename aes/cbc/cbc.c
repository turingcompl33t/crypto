// cbc.c
// Perform AES encryption / decryption in cipher block-chaining (CBC) mode. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../cipher/aes.h"
#include "../cipher/const.h"

/* ----------------------------------------------------------------------------
	Local Prototypes 
*/

static void xor(uint8_t *r, uint8_t *a, uint8_t *b); 

/* ----------------------------------------------------------------------------
	AES 128
*/

int aes_128_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t ebuf[16];  // the encryption operation buffer
	uint8_t xbuf[16];  // the XOR operation buffer 

	for (size_t block = 0; block < nblocks; block++) {
		if (block == 0) {
			// first block is special case: XOR with IV prior to encryption
			xor(xbuf, pt, iv);
		}
		else {
			// otherwise XOR with previous ciphertext block
			xor(xbuf, pt+(block*AES_BLOCK_SIZE), ebuf);
		}
		
		// do the encryption and copy result to ciphertext buffer
		aes_128_encrypt(ebuf, xbuf, key);
		memcpy(ct+(block*AES_BLOCK_SIZE), ebuf, AES_BLOCK_SIZE);
	}

	return 0; 
}

int aes_128_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t dbuf[16];   // decryption operation buffer

	for (size_t block = 0; block < nblocks; block++) {
		// do the decryption 
		aes_128_decrypt(dbuf, ct+(block*AES_BLOCK_SIZE), key);

		if (block == 0) {
			// first block is special case: XOR with IV 
			xor(pt, dbuf, iv);
		} else {
			// otherwise XOR with the previous ciphertext block
			xor(pt+(block*AES_BLOCK_SIZE), dbuf, ct+((block-1)*AES_BLOCK_SIZE));
		}
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	AES 192
*/

int aes_192_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t ebuf[16];  // the encryption operation buffer
	uint8_t xbuf[16];  // the XOR operation buffer 

	for (size_t block = 0; block < nblocks; block++) {
		if (block == 0) {
			// first block is special case: XOR with IV prior to encryption
			xor(xbuf, pt, iv);
		}
		else {
			// otherwise XOR with previous ciphertext block
			xor(xbuf, pt+(block*AES_BLOCK_SIZE), ebuf);
		}
		
		// do the encryption and copy result to ciphertext buffer
		aes_192_encrypt(ebuf, xbuf, key);
		memcpy(ct+(block*AES_BLOCK_SIZE), ebuf, AES_BLOCK_SIZE);
	}

	return 0; 
}

int aes_192_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t dbuf[16];   // decryption operation buffer

	for (size_t block = 0; block < nblocks; block++) {
		// do the decryption 
		aes_192_decrypt(dbuf, ct+(block*AES_BLOCK_SIZE), key);

		if (block == 0) {
			// first block is special case: XOR with IV 
			xor(pt, dbuf, iv);
		} else {
			// otherwise XOR with the previous ciphertext block
			xor(pt+(block*AES_BLOCK_SIZE), dbuf, ct+((block-1)*AES_BLOCK_SIZE));
		}
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	AES 256
*/

int aes_256_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t ebuf[16];  // the encryption operation buffer
	uint8_t xbuf[16];  // the XOR operation buffer 

	for (size_t block = 0; block < nblocks; block++) {
		if (block == 0) {
			// first block is special case: XOR with IV prior to encryption
			xor(xbuf, pt, iv);
		}
		else {
			// otherwise XOR with previous ciphertext block
			xor(xbuf, pt+(block*AES_BLOCK_SIZE), ebuf);
		}
		
		// do the encryption and copy result to ciphertext buffer
		aes_256_encrypt(ebuf, xbuf, key);
		memcpy(ct+(block*AES_BLOCK_SIZE), ebuf, AES_BLOCK_SIZE);
	}

	return 0; 
}

int aes_256_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv) {
	if (!ct || !pt || !key || !iv)
		return 1;

	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (len % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = len / AES_BLOCK_SIZE;

	uint8_t dbuf[16];   // decryption operation buffer

	for (size_t block = 0; block < nblocks; block++) {
		// do the decryption 
		aes_256_decrypt(dbuf, ct+(block*AES_BLOCK_SIZE), key);

		if (block == 0) {
			// first block is special case: XOR with IV 
			xor(pt, dbuf, iv);
		} else {
			// otherwise XOR with the previous ciphertext block
			xor(pt+(block*AES_BLOCK_SIZE), dbuf, ct+((block-1)*AES_BLOCK_SIZE));
		}
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// block r <- block a ^ block b
static void xor(uint8_t *r, uint8_t *a, uint8_t *b) {
	for (int i = 0; i < AES_BLOCK_SIZE; i++)
		r[i] = a[i] ^ b[i];
}
