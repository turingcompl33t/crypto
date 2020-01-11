// sha1.c
// Implementation of the SHA-1 hash function.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sha1.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void compress (uint32_t *h, uint32_t *m);
static void round_fn (uint32_t *h, uint32_t wi, size_t round);

static uint32_t f_fn_ch  (uint32_t x, uint32_t y, uint32_t z);
static uint32_t f_fn_par (uint32_t x, uint32_t y, uint32_t z);
static uint32_t f_fn_maj (uint32_t x, uint32_t y, uint32_t z);
static uint32_t rotl     (uint32_t word, size_t rot); 

static void message_schedule(uint32_t *ms, uint32_t *m_block); 

static void prepare_message(uint32_t *m_blocks, uint8_t *message, size_t len);

#ifdef DEBUG
static void debug_values (uint32_t *w, size_t round);
#endif 

/* ----------------------------------------------------------------------------
	Global Variables 
*/

// rounds constants 
static const uint32_t RC[4] = { 
	0x5a827999,  // rounds  0 - 19
	0x6ed9eba1,  // rounds 20 - 39
	0x8f1bbcdc,  // rounds 40 - 59
	0xca62c1d6   // rounds 60 - 79
};

// round function dispatch 
static uint32_t (*F_FN[4])() = {
	f_fn_ch,   // ch function
	f_fn_par,  // parity function
	f_fn_maj,  // majority function
	f_fn_par   // parity function 
};

/* ----------------------------------------------------------------------------
	Global Functions 
*/ 

// compute SHA-1 digest of message 
void sha1(uint32_t *digest, uint8_t *message, size_t len) {
	// compute total number of blocks in message
	// if message is already multiple of block size, 
	// need to add an additional block for padding block
	size_t nblocks = (len*8) / 448 + 1;
	
	// prepare + pad the input message 
	uint32_t blocks[16*nblocks]; 
	prepare_message(blocks, message, len);

	// initialization vector for iterated compression 
	uint32_t h[5] = { 0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476, 0xc3d2e1f0 };

	// for each 512-bit (64 byte) block of input message
	for (size_t block = 0; block < nblocks; block++) {
		// compress the input block
		// feedback done automatically by use of h buffer
		compress(h, blocks+(block*16)); 
	}
	
	// write the final h state to output buffer
	for (size_t i = 0; i < 5; i++) 
		digest[i] = h[i];
}

/* ----------------------------------------------------------------------------
	Local Functions - SHA-1 Compression Function
*/ 

/*
 * compress
 * SHA-1 compression function. 
 *
 * Arguments:
 * 	h - output of compression function, 5 32-bit words
 * 	m - input to compression function, 512-bit (64 byte) message block 
 */
static void compress(uint32_t *h, uint32_t *m) {
	// initialize the message schedule 
	uint32_t ms[80*32]; 
	message_schedule(ms, m);

	size_t   word;
	uint32_t working[5];

	// initialize the the working variables to current intermediate hash value
	for (word = 0; word < 5; word++)
		working[word] = h[word];

	// perform 80 iterations of round function
	for (size_t round = 0; round < 80; round++) {
		round_fn(working, ms[round], round); 
#ifdef DEBUG
		debug_values(working, round); 
#endif 
	}

	// compute the intermediate hash value
	for (word = 0; word < 5; word++)
		h[word] += working[word];
}

/* ----------------------------------------------------------------------------
	Local Functions - Message Schedule Construction
*/ 

/*
 * message_schedule
 * Construct the message schedule for compression function. 
 *
 * Arguments:
 *	ms       - output buffer for message schedule, array of 80 32-bit values
 *	m_block  - input buffer for message, 512-bit (64 byte) message block
 */
static void message_schedule(uint32_t *ms, uint32_t *m_block) {
	size_t i;
	// first 16 words of ms identical to 16 words of input block
	for (i = 0; i <= 15; i++) 
		ms[i] = m_block[i]; 
	
	// compute remaining words of message schedule 
	for (i = 16; i <= 79; i++) 
		ms[i] = rotl((ms[i - 3] ^ ms[i - 8] ^ ms[i - 14] ^ ms[i - 16]), 1);	
}

/* ----------------------------------------------------------------------------
	Local Functions - Compression Function Internals 
*/ 

/*
 * round_fn
 * Compression round function. 
 *
 * Arguments:
 *	h     - the buffer of 5 working value words 
 * 	wi    - the word from message schedule for current round
 *	round - the current round number (indexed from 0)
 */
static void round_fn(uint32_t *h, uint32_t wi, size_t round) {
	// extract individual operands from current state buffer
	uint32_t a = h[0];
	uint32_t b = h[1];
	uint32_t c = h[2];
	uint32_t d = h[3];
	uint32_t e = h[4]; 

	// compute the 'f' function 
	uint32_t f = (*F_FN[round / 20])(b, c, d); 
	// get the round constant
	uint32_t r = RC[round / 20];

	// update the state values 
	h[0] = rotl(a, 5) + f + e + wi + r; 
	h[1] = a; 
	h[2] = rotl(b, 30); 
	h[3] = c;
	h[4] = d;
}

/*
 * f_fn_ch
 * Compute the ch function, compression rounds 0 - 19
 */
static uint32_t f_fn_ch(uint32_t x, uint32_t y, uint32_t z) {
	return ((x & y) ^ (~x & z));
}

/*
 * f_fn_par
 * Compute the parity function, compression rounds 20 - 39, 60 - 79
 */
static uint32_t f_fn_par(uint32_t x, uint32_t y, uint32_t z) {
	return (x ^ y ^ z); 
}

/*
 * f_fn_maj
 * Compute the majority function, compression rounds 40 - 59
 */
static uint32_t f_fn_maj(uint32_t x, uint32_t y, uint32_t z) {
	return ((x & y) ^ (x & z) ^ (y & z)); 
}

/*
 * rotl
 * Rotate word <word> left by <rot> bits. 
 *
 * Arguments:
 *	word - input word
 *	rot  - number of positions to rotate 
 *
 * Returns:
 *	result of left word rotation
 */
static uint32_t rotl(uint32_t word, size_t rot) {
	return (word << rot) | (word >> (32 - rot)); 
}

/* ----------------------------------------------------------------------------
	Local Functions - Message Preparation
*/ 

/*
 * prepare_message
 * Pad the input message and organize into blocks. 
 *
 * Arguments:
 *	m_blocks - output buffer, 512-bit blocks, organized as 16 32-bit words
 *	message  - input buffer, raw bytes
 *  len      - length of input message, in bytes 
 */
static void prepare_message(uint32_t *m_blocks, uint8_t *msg, size_t len) {
	size_t m_idx = 0;
	size_t b_idx = 0;

	uint32_t word; 
	while (m_idx < len) {
		word = 0x00000000;
		// process 1 32-bit word at a time
		word |= (m_idx < len) ? (msg[m_idx++] << 24) : 0x80000000;
		word |= (m_idx < len) ? (msg[m_idx++] << 16) : 0x00800000;
		word |= (m_idx < len) ? (msg[m_idx++] << 8)  : 0x00008000; 
		word |= (m_idx < len) ? (msg[m_idx++])       : 0x00000080;

		m_blocks[b_idx++] = word; 
	}

	// length of input message in bits, expressed as 64-bit integer
	uint64_t padlen  = (uint64_t) (len * 8);
	// number of remaining 32-bit words needed for padding 
	size_t rem_words = 16 - (b_idx % 16); 

	// if, in final block, we are between 56 - 64 bytes of message, 
	// we need to overflow into a new block -> add an entire block of padding
	if (m_idx % 64 >= 56) 
		rem_words += 16;

	// if we ended on a word boundary when processing above, 
	// we pad with an entire word here with the 10..00 word here  
	if (m_idx % 4 == 0) {
		m_blocks[b_idx++] = 0x80000000; 
		rem_words--; 
	}

	// pad with 0..0 words until final 2 words 
	for (size_t i = 0; i < rem_words - 2; i++)
		m_blocks[b_idx++] = 0x00000000;
	// final 2 words of padding block -> original message length 
	m_blocks[b_idx++] = (uint32_t) ((padlen & 0xFFFFFFFF00000000) >> 32);
	m_blocks[b_idx++] = (uint32_t)  (padlen & 0x00000000FFFFFFFF); 	
}

/* ----------------------------------------------------------------------------
	Misc. Helpers
*/ 

#ifdef DEBUG 
static void debug_values(uint32_t *w, size_t round) {
	printf("t = %zu: %08x %08x %08x %08x %08x\n", round, w[0], w[1], w[2], w[3], w[4]); 
}
#endif 
