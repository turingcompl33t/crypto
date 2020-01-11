// ctr.c
// Perform AES encryption / decryption in CTR mode. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ctr.h"
#include "../cipher/aes.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

// size of the counter buffer, in bytes
static const int CTR_SIZE = 16;

// AES cipher block size, in bytes
static const int AES_BLOCK_SIZE = 16;

static const int CTR_OFFSET_NONCE = 0;
static const int CTR_OFFSET_COUNT = 8;

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void init_ctr(uint8_t *ctr, uint8_t *nonce);
static void inc_ctr(uint8_t *ctr);

/* ----------------------------------------------------------------------------
	Exported Functions
	See module header file (ctr.h) for detailed function comments. 
*/

// Run 128-bit AES in CTR mode to encrypt / decrypt bytes.
int aes_128_ctr_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *nonce) {
	if (!dst || ! src || !key || !nonce)
		return 1;

	// dont care if the src is not multiple of cipher block size;
	// we're in stream cipher territory here

	// initialize the counter, including the nonce 
	uint8_t ctr[CTR_SIZE];
	init_ctr(ctr, nonce);

	// buffer for the keystream output 
	uint8_t keystream[AES_BLOCK_SIZE];
	memset(keystream, 0, AES_BLOCK_SIZE); 

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		aes_128_encrypt(keystream, ctr, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++) {
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
			c_idx++; 
		}

		// increment the counter for next iteration
		inc_ctr(ctr);
	}

	return 0;
}

// Run 192-bit AES in CTR mode to encrypt / decrypt bytes.
int aes_192_ctr_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *nonce) {
	if (!dst || ! src || !key || !nonce)
		return 1;

	// dont care if the src is not multiple of cipher block size;
	// we're in stream cipher territory here

	// initialize the counter, including the nonce 
	uint8_t ctr[CTR_SIZE];
	init_ctr(ctr, nonce);

	// buffer for the keystream output 
	uint8_t keystream[AES_BLOCK_SIZE];
	memset(keystream, 0, AES_BLOCK_SIZE); 

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		aes_192_encrypt(keystream, ctr, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++) {
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
			c_idx++; 
		}

		// increment the counter for next iteration
		inc_ctr(ctr);
	}

	return 0;
}

// Run 256-bit AES in CTR mode to encrypt / decrypt bytes.
int aes_256_ctr_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *nonce) {
	if (!dst || ! src || !key || !nonce)
		return 1;

	// dont care if the src is not multiple of cipher block size;
	// we're in stream cipher territory here

	// initialize the counter, including the nonce 
	uint8_t ctr[CTR_SIZE];
	init_ctr(ctr, nonce);

	// buffer for the keystream output 
	uint8_t keystream[AES_BLOCK_SIZE];
	memset(keystream, 0, AES_BLOCK_SIZE); 

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		aes_256_encrypt(keystream, ctr, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++) {
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
			c_idx++; 
		}

		// increment the counter for next iteration
		inc_ctr(ctr);
	}

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// initialize counter, including nonce value
static void init_ctr(uint8_t *ctr, uint8_t *nonce) {
	int i;
	for (i = CTR_OFFSET_NONCE; i < (CTR_SIZE / 2); i++) 
		ctr[i] = nonce[i];
	for (; i < CTR_SIZE; i++)
		ctr[i] = 0x00;
}

// increment the counter 
static void inc_ctr(uint8_t *ctr) {
	// takes entire counter as argument
	// 64 bit nonce (little endian) || 64 bit counter (little endian)
	int word = CTR_OFFSET_COUNT; 
	while (ctr[word] == 0xFF)
		ctr[word++] = 0x00;
	ctr[word]++;
}
