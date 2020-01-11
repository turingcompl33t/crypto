// ofb.c 
// Perform AES encryption / decryption in OFB mode.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "ofb.h"
#include "../cipher/aes.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

// AES cipher block size, in bytes
static const int AES_BLOCK_SIZE = 16;

/* ----------------------------------------------------------------------------
	Exported Functions
	See module header file (ofb.h) for detailed function comments. 
*/

// Run 128-bit AES in OFB mode to encrypt / decrypt bytes.
int aes_128_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv) {
	if (!src || !dst || !key || !iv)
		return 1;

	// keystream buffer
	uint8_t keystream[AES_BLOCK_SIZE];

	// in first iteration, IV is encrypted to form keystream
	memcpy(keystream, iv, AES_BLOCK_SIZE);

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		// NOTE: this operation is safe (I know because I implemented underlying primitive)
		// but should I be doing this? -> is this bad practice? 
		aes_128_encrypt(keystream, keystream, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++, c_idx++) 
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
	}

	return 0; 
}

// Run 192-bit AES in OFB mode to encrypt / decrypt bytes.
int aes_192_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv) {
	if (!src || !dst || !key || !iv)
		return 1;

	// keystream buffer
	uint8_t keystream[AES_BLOCK_SIZE];

	// in first iteration, IV is encrypted to form keystream
	memcpy(keystream, iv, AES_BLOCK_SIZE);

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		// NOTE: this operation is safe (I know because I implemented underlying primitive)
		// but should I be doing this? -> is this bad practice? 
		aes_192_encrypt(keystream, keystream, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++, c_idx++) 
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
	}

	return 0; 
}

// Run 256-bit AES in OFB mode to encrypt / decrypt bytes.
int aes_256_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv) {
	if (!src || !dst || !key || !iv)
		return 1;

	// keystream buffer
	uint8_t keystream[AES_BLOCK_SIZE];

	// in first iteration, IV is encrypted to form keystream
	memcpy(keystream, iv, AES_BLOCK_SIZE);

	int c_idx;  // cipher index
	int b_idx;  // block index

	for (c_idx = 0; c_idx < nbytes;) {
		// get the next 16 bytes of the keystream
		// NOTE: this operation is safe (I know because I implemented underlying primitive)
		// but should I be doing this? -> is this bad practice? 
		aes_256_encrypt(keystream, keystream, key);

		// encrypt the next 16 bytes (possibly fewer) using keystream
		for (b_idx = 0; (b_idx < AES_BLOCK_SIZE) && (c_idx < nbytes); b_idx++, c_idx++) 
			dst[c_idx] = (src[c_idx] ^ keystream[b_idx]);
	}

	return 0; 
}
