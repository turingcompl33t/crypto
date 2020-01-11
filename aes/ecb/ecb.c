// ecb.c
// Perform AES encryption / decryption in electronic codebook (ECB) mode. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "../cipher/aes.h"
#include "../cipher/const.h"

/* ----------------------------------------------------------------------------
	AES 128 
*/

// perform 128-bit AES encryption in ECB mode
int aes_128_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: encrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_128_encrypt(ct+(block*AES_BLOCK_SIZE), pt+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}

// perform 128-bit AES decryption in ECB mode
int aes_128_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: ciphertext must be multiple of cipher blocksize (16 bytes) to decrypt\n");
		fprintf(stderr, "ERROR: consider padding your ciphertext prior to calling this function...\n");
		return 1;
	}

	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: decrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_128_decrypt(pt+(block*AES_BLOCK_SIZE), ct+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	AES 192
*/

// perform 192-bit AES encryption in ECB mode
int aes_192_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: encrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_192_encrypt(ct+(block*AES_BLOCK_SIZE), pt+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}

// perform 192-bit AES decryption in ECB mode
int aes_192_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: ciphertext must be multiple of cipher blocksize (16 bytes) to decrypt\n");
		fprintf(stderr, "ERROR: consider padding your ciphertext prior to calling this function...\n");
		return 1;
	}

	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: decrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_192_decrypt(pt+(block*AES_BLOCK_SIZE), ct+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	AES 256
*/

// perform 256-bit AES encryption in ECB mode
int aes_256_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: plaintext must be multiple of cipher blocksize (16 bytes) to encrypt\n");
		fprintf(stderr, "ERROR: consider padding your plaintext prior to calling this function...\n");
		return 1;
	}
		
	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: encrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_256_encrypt(ct+(block*AES_BLOCK_SIZE), pt+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}

// perform 256-bit AES decryption in ECB mode
int aes_256_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key) {
	// we require that caller takes care of padding prior to invocation
	// alternatively, could do it for them, but we like low coupling in code
	if (nbytes % AES_BLOCK_SIZE != 0) {
		fprintf(stderr, "ERROR: ciphertext must be multiple of cipher blocksize (16 bytes) to decrypt\n");
		fprintf(stderr, "ERROR: consider padding your ciphertext prior to calling this function...\n");
		return 1;
	}

	size_t nblocks = nbytes / AES_BLOCK_SIZE;
		
	// ECB mode: decrypt each block independently
	for (size_t block = 0; block < nblocks; block++) {
		aes_256_decrypt(pt+(block*AES_BLOCK_SIZE), ct+(block*AES_BLOCK_SIZE), key); 
	}

	return 0; 
}


