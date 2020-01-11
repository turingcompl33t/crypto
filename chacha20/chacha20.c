// chacha20.c
// Implementation of the Chacha20 stream cipher. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "chacha20.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

// internal state constants
static const uint32_t C0 = 0x61707865;
static const uint32_t C1 = 0x3320646e;
static const uint32_t C2 = 0x79622d32;
static const uint32_t C3 = 0x6b206574;

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void cr(uint32_t *state);
static void dr(uint32_t *state);
static void qr(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d);

static void pack(uint32_t *state, uint8_t *key, uint8_t *nonce, uint32_t ctr);
static void unpack(uint8_t *block, uint32_t *state);

static uint32_t le(uint8_t *bytes);
static void lei(uint8_t *bytes, uint32_t word);

static void rotl(uint32_t *n, size_t nbits);
static void print_state(uint32_t *state); 

/* ----------------------------------------------------------------------------
	Exported Functions - Chacha20 Cipher
*/

// encrypt / decrypt data with chacha20 stream cipher
int chacha20_cipher(uint8_t *ct,  uint8_t *pt,    size_t mlen, 
					uint8_t *key, uint8_t *nonce, uint32_t ctr) {

	// buffer for successive keystream blocks
	uint8_t keystream[64];

	int midx;  // message index
	int bidx;  // block index

	for (midx = 0; midx < mlen;) {
		// compute the next block of keystream
		chacha20_core(keystream, key, nonce, ctr++);
		// apply keystream to plaintext to compute ciphertext
		for (bidx = 0; (bidx < 64) && (midx < mlen); bidx++, midx++) 
			ct[midx] = pt[midx] ^ keystream[bidx]; 
	}

	return 0;
}

/* ----------------------------------------------------------------------------
	Exported Functions - Chacha20 Core
*/

// compute the chacha20 core function
int chacha20_core(uint8_t *block, uint8_t *key, uint8_t *nonce, uint32_t ctr) {
	uint32_t x[16];  // static internal state buffer
	uint32_t z[16];  // working internal state buffer
	pack(x, key, nonce, ctr);
	pack(z, key, nonce, ctr);

	#ifdef DEBUG
	printf("[DEBUG] initial state (block counter %u):\n", ctr);
	print_state(z);
	#endif

	// apply 10 doubleround iterations;
	// yielding a total of 20 rounds 
	for (int i = 0; i < 10; i++) {
		cr(z);  // 4 x quarterround
		dr(z);  // 4 x quarterround
	}

	#ifdef DEBUG
	puts("[DEBUG] after 20 rounds:");
	print_state(z);
	#endif

	// add original state to result
	for(int i = 0; i < 16; i++)
		z[i] += x[i];

	#ifdef DEBUG
	puts("[DEBUG] after addition with original state:");
	print_state(z);
	#endif

	// serialize result vector to output block
	unpack(block, z);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions - Round Functions
*/

// compute column round on internal state vector
static void cr(uint32_t *state) {
	qr(state,   state+4, state+8,  state+12);
	qr(state+1, state+5, state+9,  state+13);
	qr(state+2, state+6, state+10, state+14);
	qr(state+3, state+7, state+11, state+15);
}

// compute diagonal round on internal state vector
static void dr(uint32_t *state) {
	qr(state,   state+5, state+10, state+15);
	qr(state+1, state+6, state+11, state+12);
	qr(state+2, state+7, state+8,  state+13);
	qr(state+3, state+4, state+9,  state+14);
}

// compute quarterround function; "the heart of Chacha20"
static void qr(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d) {
	*a += *b; *d ^= *a; rotl(d, 16);
	*c += *d; *b ^= *c; rotl(b, 12);
	*a += *b; *d ^= *a; rotl(d,  8);
	*c += *d; *b ^= *c; rotl(b,  7);
}

/* ----------------------------------------------------------------------------
	Local Functions - Internal State Formation
*/

// pack internal state vector from bytes
static void pack(uint32_t *state, uint8_t *key, uint8_t *nonce, uint32_t ctr) {
	int sidx = 0;  // state index
	
	// pack constant values
	state[sidx++] = C0;
	state[sidx++] = C1;
	state[sidx++] = C2;
	state[sidx++] = C3;

	// pack 256 bit (32 byte) key
	for (int i = 0; i < 32; i += 4) 
		state[sidx++] = le(key+i);

	// pack block counter
	state[sidx++] = ctr;

	// pack 96 bit (12 byte) nonce
	for (int i = 0; i < 12; i += 4) 
		state[sidx++] = le(nonce+i);
}

// unpack internal state vector to bytes 
static void unpack(uint8_t *block, uint32_t *state) {
	uint8_t bytes[4];
	for (int i = 0; i < 16; i++) {
		lei(bytes, state[i]);
		block[i*4]   = bytes[0];
		block[i*4+1] = bytes[1];
		block[i*4+2] = bytes[2];
		block[i*4+3] = bytes[3];
	}

}

/* ----------------------------------------------------------------------------
	Local Functions - Misc. Helpers
*/

// pack 4 bytes into 32-bit little-endian word
static uint32_t le(uint8_t *bytes) {
	return (bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0];
}

// unpack 32-bit little-endian word to bytes
static void lei(uint8_t *bytes, uint32_t word) {
	bytes[0] = (uint8_t) word;
	bytes[1] = (uint8_t) (word >> 8);
	bytes[2] = (uint8_t) (word >> 16);
	bytes[3] = (uint8_t) (word >> 24);
}

// rotate word <n> left by <nbits> bits
static void rotl(uint32_t *n, size_t nbits) {
	*n = (*n << nbits) | (*n >> (32 - nbits)); 
}

// print internal state vector
static void print_state(uint32_t *state) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			printf("%08x ", state[i*4+j]);
		putchar('\n');
	}
}
