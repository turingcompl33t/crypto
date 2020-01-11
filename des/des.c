// des.c
// Data Encryption Standard cipher implementation. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "perm.h"
#include "util.h"
#include "const.h"
#include "feistel.h"
#include "key_schedule.h"

/* ----------------------------------------------------------------------------
    Global Functions
    See module header file (des.h) for detailed function comments. 
*/

// perform DES encryption
int des_encrypt(uint8_t *ct, uint8_t *pt, uint8_t *key) {

#ifdef DEBUG
	printf("[DEBUG] DES ENCRYPT\n");
	printf("%-20s", "PLAINTEXT:");
	hexdump(pt, DES_BLOCK_SIZE_BYTES);
	printf("%-20s", "KEY:");
	hexdump(key, DES_BLOCK_SIZE_BYTES);
#endif

	// initialize internal state
	uint8_t *state = calloc(DES_BLOCK_SIZE_BYTES, sizeof(uint8_t));

	// initialize key schedule 
	uint8_t *key_schedule = calloc(DES_NROUNDS*DES_SUBKEY_SIZE_BYTES, sizeof(uint8_t));
	expand_key(key, key_schedule);

	// perform initial permutation 
	ip(pt, state);

#ifdef DEBUG
	printf("%-20s", "IP:");
	hexdump(state, DES_BLOCK_SIZE_BYTES);
#endif

	// 16 rounds through feistel network
	for (int round = 0; round < DES_NROUNDS; round++) {
		// compute the round subkey for each round as offset into key schedule 
		feistel(state, key_schedule+(round*DES_SUBKEY_SIZE_BYTES)); 

#ifdef DEBUG
		printf("(%2d) %-15s", round+1, "STATE:");
		hexdump(state, DES_BLOCK_SIZE_BYTES);
		printf("(%2d) %-15s", round+1, "SUBKEY:");
		hexdump(key_schedule + (round*6), DES_SUBKEY_SIZE_BYTES);
#endif
	}

	// undo the final 'swap' within feistel construction
	swap_halves(state); 

#ifdef DEBUG
	printf("%-20s", "FINAL SWAP:");
	hexdump(state, DES_BLOCK_SIZE_BYTES); 
#endif 

	// perform final permutation 
	inv_ip(state, ct);

#ifdef DEBUG
	printf("%-20s", "INVERSE IP:");
	hexdump(ct, DES_BLOCK_SIZE_BYTES); 
	printf("%-20s", "ENCRYPT OUTPUT:");
	hexdump(ct, DES_BLOCK_SIZE_BYTES); 
#endif 

	// cleanup
	free(state);
	free(key_schedule); 

	return 0; 
}

// perform DES decryption
int des_decrypt(uint8_t *pt, uint8_t *ct, uint8_t *key) {

#ifdef DEBUG
	printf("[DEBUG] DES DECRYPT\n");
	printf("%-20s", "CIPHERTEXT:");
	hexdump(ct, DES_BLOCK_SIZE_BYTES);
	printf("%-20s", "KEY:");
	hexdump(key, DES_BLOCK_SIZE_BYTES);
#endif

	// initialize internal state
	uint8_t *state = calloc(DES_BLOCK_SIZE_BYTES, sizeof(uint8_t));

	// initialize key schedule 
	uint8_t *key_schedule = calloc(DES_NROUNDS*DES_SUBKEY_SIZE_BYTES, sizeof(uint8_t));
	expand_key(key, key_schedule);

	// perform initial permutation 
	ip(ct, state);

#ifdef DEBUG
	printf("%-20s", "IP:");
	hexdump(state, DES_BLOCK_SIZE_BYTES);
#endif

	// 16 rounds through feistel network
	for (int round = 15; round >= 0; round--) {
		// compute the round subkey for each round as offset into key schedule 
		// cool part about DES: because encryption is accomplished via simple XOR, 
		// we invert the encryption operation (i.e. decrypt) by XORing again 
		// against SAME block used during encryption
		// the takeaway message: to decrypt, just reverse the order of key schedule
		feistel(state, key_schedule+(round*DES_SUBKEY_SIZE_BYTES)); 

#ifdef DEBUG
		printf("(%2d) %-15s", round+1, "STATE:");
		hexdump(state, DES_BLOCK_SIZE_BYTES);
		printf("(%2d) %-15s", round+1, "SUBKEY:");
		hexdump(key_schedule + (round*6), DES_SUBKEY_SIZE_BYTES);
#endif
	}

	// undo the final 'swap' within feistel construction
	swap_halves(state); 

#ifdef DEBUG
	printf("%-20s", "FINAL SWAP:");
	hexdump(state, DES_BLOCK_SIZE_BYTES); 
#endif 

	// perform final permutation 
	inv_ip(state, pt);

#ifdef DEBUG
	printf("%-20s", "INVERSE IP:");
	hexdump(pt, DES_BLOCK_SIZE_BYTES); 
	printf("%-20s", "DECRYPT OUTPUT:");
	hexdump(pt, DES_BLOCK_SIZE_BYTES); 
#endif 

	// cleanup
	free(state);
	free(key_schedule); 

	return 0;
}

// perform 3DES encryption
int des3_encrypt(uint8_t *ct, uint8_t *pt, uint8_t *k1, uint8_t *k2, uint8_t *k3) {
	uint8_t tmp1[8];
	uint8_t tmp2[8];

	// encrypt under k1
	des_encrypt(tmp1, pt, k1);
	// decrypt under k2
	des_decrypt(tmp2, tmp1, k2);
	// encrypt under k3
	des_encrypt(ct, tmp2, k3);

	return 0; 
}

// perform 3DES decryption
int des3_decrypt(uint8_t *pt, uint8_t *ct, uint8_t *k1, uint8_t *k2, uint8_t *k3) {
	uint8_t tmp1[8];
	uint8_t tmp2[8];

	// decrypt under k3
	des_decrypt(tmp1, ct, k3);
	// encrypt under k2
	des_encrypt(tmp2, tmp1, k2);
	// decrypt under k1
	des_decrypt(pt, tmp2, k1);

	return 0;
}
