// key_schedule.c
// Key schedule generation routines. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mul.h"
#include "util.h"
#include "const.h"
#include "sub_bytes.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

void get_rcon(uint8_t *rcon, size_t i, size_t nwords);
void sub_word(uint8_t *word);
void rot_word(uint8_t *word);
void xor_word(uint8_t *dst, uint8_t *src_a, uint8_t *src_b);

/* ----------------------------------------------------------------------------
	Global Functions - Round Key Addition 
	See module header file (key_schedule.h) for detailed function comments. 
*/

// add round key to current state matrix 
void add_round_key(uint8_t *state, uint8_t *round_key) {
	uint8_t val;
	for (size_t col = 0; col < 4; col++) {
		for (size_t row = 0; row < 4; row++) {
			val = mget(state, row, col) ^ mget(round_key, row, col); 
			mset(state, row, col, val); 
		}
	}
}

/* ----------------------------------------------------------------------------
	Global Functions - Key Expansion 
	See module header file (key_schedule.h) for detailed function comments. 
*/

// expand cipher key according to key schedule algorithm 
void expand_key(uint8_t *key, uint8_t *key_schedule, size_t nwords, size_t nrounds) {
	size_t i;
	uint8_t tmp[4]; 
	uint8_t rcon[4]; 

	for (i = 0; i < nwords*4; i+=4) {
		key_schedule[i] = key[i];
		key_schedule[i+1] = key[i+1];
		key_schedule[i+2] = key[i+2];
		key_schedule[i+3] = key[i+3];
	}

	i = nwords;

	while (i < AES_BLOCK_WORDS * (nrounds + 1)) {
		tmp[0] = key_schedule[i*4 - 4];
		tmp[1] = key_schedule[i*4 - 4 + 1];
		tmp[2] = key_schedule[i*4 - 4 + 2];
		tmp[3] = key_schedule[i*4 - 4 + 3];

		if (i % nwords == 0) {
			rot_word(tmp); 
			sub_word(tmp);
			get_rcon(rcon, i, nwords);
			xor_word(tmp, tmp, rcon); 
		} else if (nwords > 6 && i % nwords == 4) {
			// special case for 256-bit key 
			sub_word(tmp); 
		}

		key_schedule[i*4]   = key_schedule[i*4 - 4*nwords]     ^ tmp[0];
		key_schedule[i*4+1] = key_schedule[i*4 - 4*nwords + 1] ^ tmp[1];
		key_schedule[i*4+2] = key_schedule[i*4 - 4*nwords + 2] ^ tmp[2];
		key_schedule[i*4+3] = key_schedule[i*4 - 4*nwords + 3] ^ tmp[3];

		i++;
	}
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// generate the round constant 
void get_rcon(uint8_t *rcon, size_t i, size_t nwords) {
	rcon[0] = ixmul(0x01, (i / nwords) - 1); 
	rcon[1] = 0x00;
	rcon[2] = 0x00;
	rcon[3] = 0x00;
}

// applies substitution box to word 
void sub_word(uint8_t *word) {
	for (size_t i = 0; i < 4; i++) {
		word[i] = sub_byte(word[i]);
	}
}

// performs a leftward cyclic permutation
void rot_word(uint8_t *word) {
	uint8_t tmp = word[0];
	word[0] = word[1];
	word[1] = word[2];
	word[2] = word[3];
	word[3] = tmp; 
}

// perform dst <- src_a XOR src_b (intel syntax)
void xor_word(uint8_t *dst, uint8_t *src_a, uint8_t *src_b) {
	for (size_t i = 0; i < 4; i++) {
		dst[i] = (src_a[i] ^ src_b[i]);
	}
}
