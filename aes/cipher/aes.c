// aes.c 
// AES algorithm implementation. 

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"
#include "util.h"
#include "const.h"
#include "mix_cols.h"
#include "sub_bytes.h"
#include "shift_rows.h"
#include "key_schedule.h"

/* ----------------------------------------------------------------------------
	AES 128
*/

// perform 128-bit AES encryption
int aes_128_encrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_128_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_128_KEY_WORDS, AES_128_NROUNDS);

	#ifdef DEBUG
	puts("encrypt input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule);

	size_t round;
	for (round = 1; round < AES_128_NROUNDS; round++) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);
		#endif

		sub_bytes(state); 
		shift_rows(state);
		mix_cols(state);
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	sub_bytes(state);
	shift_rows(state);
	add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4));

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}

// perform 128-bit AES decryption
int aes_128_decrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_128_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_128_KEY_WORDS, AES_128_NROUNDS);

	#ifdef DEBUG
	puts("decrypt input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule+(AES_128_NROUNDS*AES_BLOCK_WORDS*4));

	size_t round;
	for (round = AES_128_NROUNDS - 1; round >= 1; round--) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);
		#endif

		inv_shift_rows(state);
		inv_sub_bytes(state); 
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
		inv_mix_cols(state);
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, key_schedule);

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}

/* ----------------------------------------------------------------------------
	AES 192
*/

// perform 192-bit AES encryption
int aes_192_encrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_192_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_192_KEY_WORDS, AES_192_NROUNDS);

	#ifdef DEBUG
	puts("input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule);

	size_t round;
	for (round = 1; round < AES_192_NROUNDS; round++) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);
		#endif

		sub_bytes(state); 
		shift_rows(state);
		mix_cols(state);
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	sub_bytes(state);
	shift_rows(state);
	add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4));

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}

// perform 192-bit AES decryption
int aes_192_decrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_192_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_192_KEY_WORDS, AES_192_NROUNDS);

	#ifdef DEBUG
	puts("decrypt input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule+(AES_192_NROUNDS*AES_BLOCK_WORDS*4));

	size_t round;
	for (round = AES_192_NROUNDS - 1; round >= 1; round--) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);
		#endif

		inv_shift_rows(state);
		inv_sub_bytes(state); 
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
		inv_mix_cols(state);
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, key_schedule);

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}

/* ----------------------------------------------------------------------------
	AES 256
*/

// perform 256-bit AES encryption
int aes_256_encrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_256_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_256_KEY_WORDS, AES_256_NROUNDS);

	#ifdef DEBUG
	puts("input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule);

	size_t round;
	for (round = 1; round < AES_256_NROUNDS; round++) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);

		#endif
		sub_bytes(state); 
		shift_rows(state);
		mix_cols(state);
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	sub_bytes(state);
	shift_rows(state);
	add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4));

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}

// perform 256-bit AES decryption
int aes_256_decrypt(uint8_t *out, uint8_t *in, uint8_t *key) {
	// initialize internal state 
	uint8_t *state = calloc(AES_BLOCK_SIZE, sizeof(uint8_t));
	memcpy((char *) state, (char *) in, AES_BLOCK_SIZE); 

	// generate key schedule via key expansion 
	uint8_t *key_schedule = calloc(AES_BLOCK_SIZE*(AES_256_NROUNDS+1), sizeof(uint8_t));
	expand_key(key, key_schedule, AES_256_KEY_WORDS, AES_256_NROUNDS);

	#ifdef DEBUG
	puts("decrypt input");
	print_state(state);
	#endif

	// initial round key addition  
	add_round_key(state, key_schedule+(AES_256_NROUNDS*AES_BLOCK_WORDS*4));

	size_t round;
	for (round = AES_256_NROUNDS - 1; round >= 1; round--) {

		#ifdef DEBUG
		printf("start of round %zu\n", round);
		print_state(state);
		#endif

		inv_shift_rows(state);
		inv_sub_bytes(state); 
		add_round_key(state, key_schedule+(round*AES_BLOCK_WORDS*4)); 
		inv_mix_cols(state);
	}

	#ifdef DEBUG
	puts("start of final round");
	print_state(state);
	#endif 

	inv_shift_rows(state);
	inv_sub_bytes(state);
	add_round_key(state, key_schedule);

	// write final state to output buffer
	memcpy((char *) out, (char *) state, AES_BLOCK_SIZE); 

	// cleanup 
	free(state); 
	free(key_schedule); 

	return 0;
}
