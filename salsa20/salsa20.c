// salsa20.c
// Implementation of the Salsa20 stream cipher.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "salsa20.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

// state expansion constants: 32-byte keys
uint32_t SIGMA_0 = 0x61707865;
uint32_t SIGMA_1 = 0x3320646e;
uint32_t SIGMA_2 = 0x79622d32;
uint32_t SIGMA_3 = 0x6b206574; 

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void state_init(uint32_t *state, uint8_t *key, uint8_t *nonce, uint64_t ctr);
static void state_copy(uint32_t *dst, uint32_t *src);

static void dr(uint32_t *state);
static void rr(uint32_t *state);
static void cr(uint32_t *state);

static void qr(uint32_t *z0, uint32_t *z1, uint32_t *z2, uint32_t *z3);

static uint32_t le(uint8_t *bytes);
static void     lei(uint8_t *bytes, uint32_t word);
static uint32_t rotl(uint32_t word, size_t rot);
static void 	print_state(uint32_t *state);
static void 	print_bytes(uint8_t *bytes);

/* ----------------------------------------------------------------------------
	Exported Functions
*/

// salsa20 stream cipher
int salsa20(uint8_t *out, uint8_t *in, size_t mlen, uint8_t *key, uint8_t *nonce) {
	if (!out || !in)
		return 1;

	// buffer for keystream blocks
	uint8_t keystream[64];

	size_t   midx;     // message index
	size_t   bidx;     // block index
	uint64_t ctr = 1;  // keystream counter

	for (midx = 0; midx < mlen;) {
		// generate next 64 bytes of keystream
		salsa20_core(keystream, key, nonce, ctr++);
		// and apply keystream to input
		for (bidx = 0; (bidx < 64) && (midx < mlen); midx++, bidx++)
			out[midx] = in[midx] ^ keystream[bidx];
	}
	
	return 0; 
}

// the salsa20 core function
void salsa20_core(uint8_t *block, uint8_t *key, uint8_t *nonce, uint64_t ctr) {
	// buffers for internal state: 16 32-bit words
	uint32_t x[16];
	uint32_t z[16];

	// prepare the internal state
	state_init(x, key, nonce, ctr);
	state_copy(z, x);

#ifdef DEBUG
	printf("init state for ctr  = %llu\n", ctr);
	print_state(x);
#endif 

	// apply 10 iterations of doubleround function
	for (int i = 0; i < 10; i++) 
		dr(z);

#ifdef DEBUG
	printf("final state for ctr = %llu\n", ctr);
	print_state(z);
#endif 

	// finalize output buffer:
	// compute z0 + x0, unpack word to bytes
	for (int i = 0; i < 16; i++) 
		lei(block+(i*4), z[i] + x[i]);
}

// generalized version of salsa20 core function
void salsa20_hash(uint8_t *out, uint8_t *in) {
	// buffer for internal state: 16 32-bit words
	uint32_t state[16];

	// prepare the internal state
	for (int i = 0; i < 16; i++) 
		state[i] = le(in+(i*4));

	// apply 10 iterations of doubleround function
	for (int i = 0; i < 10; i++) 
		dr(state);

	// compute z0 + x0, unpack word to bytes
	for (int i = 0; i < 16; i++) 
		lei(out+(i*4), state[i] + le(in+(i*4)));
}

/* ----------------------------------------------------------------------------
	Local Functions - State Initialization
*/

// prepare internal state array for salsa20 core
static void state_init(uint32_t *state, uint8_t *key, uint8_t *nonce, uint64_t ctr) {
	state[0] = SIGMA_0;
	for (int i = 0; i < 4; i++)         // offset = 1
		state[i+1] = le(key+(i*4));
	state[5] = SIGMA_1;
	for (int i = 0; i < 2; i++)         // offset = 6
		state[6+i] = le(nonce+(i*4));
	state[8] = (uint32_t) ctr; 
	state[9] = (uint32_t) (ctr >> 32);
	state[10] = SIGMA_2;
	for (int i = 0; i < 4; i++)         // offset = 11
		state[i+11] = le(key+16+(i*4));
	state[15] = SIGMA_3;
}

// copy state array representation for salsa20 core
static void state_copy(uint32_t *dst, uint32_t *src) {
	for (int i = 0; i < 16; i++)
		dst[i] = src[i]; 
}

/* ----------------------------------------------------------------------------
	Local Functions - Round Functions
*/

// compute the doubleround function
static void dr(uint32_t *state) {
	cr(state);
	rr(state);
}

// compute the rowround function
static void rr(uint32_t *state) {
	// state is a 16 word sequence (4x4 matrix)
	qr(&state[0],  &state[1],  &state[2],  &state[3]);
	qr(&state[5],  &state[6],  &state[7],  &state[4]);
	qr(&state[10], &state[11], &state[8],  &state[9]);
	qr(&state[15], &state[12], &state[13], &state[14]);
}

// compute the columnround function
static void cr(uint32_t *state) {
	// state is a 16 word sequence (4x4 matrix)
	qr(&state[0],  &state[4],  &state[8],  &state[12]);
	qr(&state[5],  &state[9],  &state[13], &state[1]);
	qr(&state[10], &state[14], &state[2],  &state[6]);
	qr(&state[15], &state[3],  &state[7],  &state[11]);
}

// compute the quarterround function
static void qr(uint32_t *z0, uint32_t *z1, uint32_t *z2, uint32_t *z3) {
	*z1 ^= rotl((*z0 + *z3), 7);
	*z2 ^= rotl((*z1 + *z0), 9);
	*z3 ^= rotl((*z2 + *z1), 13);
	*z0 ^= rotl((*z3 + *z2), 18);	
}

/* ----------------------------------------------------------------------------
	Local Functions - Helpers
*/

// pack little endian word into word
static uint32_t le(uint8_t *bytes) {
	return (uint32_t) (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
}

// unpack little endian word into bytes
static void lei(uint8_t *bytes, uint32_t word) {
	bytes[0] = (uint8_t) (word);
	bytes[1] = (uint8_t) (word >> 8);
	bytes[2] = (uint8_t) (word >> 16);
	bytes[3] = (uint8_t) (word >> 24);
}

// rotate word left by <rot> bits
static uint32_t rotl(uint32_t word, size_t rot) {
	return (word << rot) | (word >> (32 - rot));
}

// print the internal state to stdout 
static void print_state(uint32_t *state) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%08x ", state[i*4+j]);
		putchar('\n');
	}
}

// print input / output byte vector to stdout
static void print_bytes(uint8_t *bytes) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++)
			printf("%02x ", bytes[i*16+j]);
		putchar('\n');
	}
}
