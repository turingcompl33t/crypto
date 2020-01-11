// feistel.c
// Cipher feistel network. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "util.h"
#include "feistel.h"

/* ----------------------------------------------------------------------------
    Local Constants 
*/

// E bit selection function 
static const int E_FN[] = {
	32,  1,  2,  3,  4,  5,
	 4,  5,  6,  7,  8,  9,
	 8,  9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32,  1 
};

// selection function 1
static const uint8_t S1[][16] = {
	{ 14,  4, 13, 1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9, 0,  7 },
	{  0, 15,  7, 4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5, 3,  8 },
	{  4,  1, 14, 8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10, 5,  0 },
	{ 15, 12,  8, 2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0, 6, 13 }
};

// selection function 2
static const uint8_t S2[][16] = {
	{ 15,  1,  8, 14,  6, 11,  3,  4,  9, 7,  2, 13, 12, 0,  5, 10 },
	{  3, 13,  4,  7, 15,  2,  8, 14, 12, 0,  1, 10,  6, 9, 11,  5 },
	{  0, 14,  7, 11, 10,  4, 13,  1,  5, 8, 12,  6,  9, 3,  2, 15 },
	{ 13,  8, 10,  1,  3, 15,  4,  2, 11, 6,  7, 12,  0, 5, 14,  9 }
};

// selection function 3
static const uint8_t S3[][16] = {
	{ 10,  0,  9, 14, 6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 },
	{ 13,  7,  0,  9, 3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1 },
	{ 13,  6,  4,  9, 8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7 },
	{  1, 10, 13,  0, 6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12 }
};

// selection function 4
static const uint8_t S4[][16] = {
	{  7, 13, 14, 3,  0,  6,  9, 10,  1, 2, 8,  5, 11, 12,  4, 15 },
	{ 13,  8, 11, 5,  6, 15,  0,  3,  4, 7, 2, 12,  1, 10, 14,  9 },
	{ 10,  6,  9, 0, 12, 11,  7, 13, 15, 1, 3, 14,  5,  2,  8,  4 },
	{  3, 15,  0, 6, 10,  1, 13,  8,  9, 4, 5, 11, 12,  7,  2, 14 }
};

// selection function 5
static const uint8_t S5[][16] = {
	{  2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13, 0, 14,  9 },
	{ 14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3, 9,  8,  6 },
	{  4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6, 3,  0, 14 },
	{ 11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10, 4,  5,  3 }
};

// selection function 6
static const uint8_t S6[][16] = {
	{ 12,  1, 10, 15, 9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 },
	{ 10, 15,  4,  2, 7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8 },
	{  9, 14, 15,  5, 2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6 },
	{  4,  3,  2, 12, 9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13 }
};

// selection function 7
static const uint8_t S7[][16] = {
	{  4, 11,  2, 14, 15, 0,  8, 13,  3, 12, 9,  7,  5, 10, 6,  1 },
	{ 13,  0, 11,  7,  4, 9,  1, 10, 14,  3, 5, 12,  2, 15, 8,  6 },
	{  1,  4, 11, 13, 12, 3,  7, 14, 10, 15, 6,  8,  0,  5, 9,  2 },
	{  6, 11, 13,  8,  1, 4, 10,  7,  9,  5, 0, 15, 14,  2, 3, 12 }
};

// selection function 8
static const uint8_t S8[][16] = {
	{ 13,  2,  8, 4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 },
	{  1, 15, 13, 8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2 },
	{  7, 11,  4, 1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8 },
	{  2,  1, 14, 7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11 }
};

// permutation function
static const int P_FN[] = {
	16,  7, 20, 21,
	29, 12, 28, 17,
	 1, 15, 23, 26,
	 5, 18, 31, 10,
	 2,  8, 24, 14,
	32, 27,  3,  9,
	19, 13, 30,  6,
	22, 11,  4, 25 
};

/* ----------------------------------------------------------------------------
    Local Prototypes
*/

static void e_bit_selection(uint8_t *out, uint8_t *in); 

static void select(uint8_t *out, uint8_t *in);
static void select_s1(uint8_t *out, uint8_t *in);
static void select_s2(uint8_t *out, uint8_t *in);
static void select_s3(uint8_t *out, uint8_t *in);
static void select_s4(uint8_t *out, uint8_t *in);
static void select_s5(uint8_t *out, uint8_t *in);
static void select_s6(uint8_t *out, uint8_t *in);
static void select_s7(uint8_t *out, uint8_t *in);
static void select_s8(uint8_t *out, uint8_t *in);

static void permute(uint8_t *out, uint8_t *in);

static uint8_t get_col(uint8_t byte);
static uint8_t get_row(uint8_t byte);

static void trace_sbox(const uint8_t sbox[4][16], const char *str, 
					   uint8_t in, uint8_t row, uint8_t col, uint8_t out);

/* ----------------------------------------------------------------------------
    Exported Functions
    See module header file (des.h) for detailed function comments. 
*/

// perform single iteration of feistel network 
void feistel(uint8_t *state, uint8_t *subkey) {
	uint8_t l_next[4] = { 0 };  // buffer for l of next state
	uint8_t r_next[4] = { 0 };  // buffer for r of next state 

	// l_next <- r
	memcpy((char *) l_next, (char *) state + 4, 4);

#ifdef TRACE
	printf("%-20s", "INPUT STATE:");
	hexdump(state, 8);
#endif

	// goal: r_next <- l XOR f(r, k_n)

	// step 1. r_next <- f (r, k_n)
	cipher_f(r_next, state + 4, subkey);

#ifdef TRACE
	printf("%-20s", "FUNCTION OUT:");
	hexdump(r_next, 4);
#endif

	// step 2. r_next <- r_next XOR l
	xor_blocks(r_next, r_next, state, 4); 

#ifdef TRACE
	printf("%-20s", "XOR:");
	hexdump(r_next, 4);
#endif 

	// finalize the next state of cipher
	memcpy((char *) state,     (char *) l_next, 4);
	memcpy((char *) state + 4, (char *) r_next, 4); 
}

// r_next <- f(r, k_n)
void cipher_f(uint8_t *r_next, uint8_t *r, uint8_t *subkey) {
	// local state buffers
	uint8_t lstate_4[4] = { 0 };
	uint8_t lstate_6[6] = { 0 };

#ifdef TRACE
	printf("%-20s", "INPUT R:");
	hexdump(r, 4);
	printf("%-20s", "INPUT SUBKEY:");
	hexdump(subkey, 6);
#endif 

	// perform the E bit selection function 
	// expand 48 bit local state <- 32 bit r
	e_bit_selection(lstate_6, r); 

#ifdef TRACE
	printf("%-20s", "E EXPANSION:");
	hexdump(lstate_6, 6);
#endif 

	// perform local state XOR round subkey
	xor_blocks(lstate_6, lstate_6, subkey, 6);

#ifdef TRACE
	printf("%-20s", "SUBKEY ADDITION:");
	hexdump(lstate_6, 6);
#endif

	// selection functions 
	// compress 32 bit state <- 48 bit state
	select(lstate_4, lstate_6);

#ifdef TRACE
	printf("%-20s", "SUBSTITUTION:");
	hexdump(lstate_4, 4);
#endif 

	// permutation function 
	// permute r_next <- 32 bit state 
	permute(r_next, lstate_4); 

#ifdef TRACE
	printf("%-20s", "PERMUTATION:");
	hexdump(r_next, 4);
#endif 
}

void swap_halves(uint8_t *state) {
	uint8_t tmp[4];
	memcpy(tmp, state, 4);      // tmp  <- left
	memcpy(state, state+4, 4);  // left <- right
	memcpy(state+4, tmp, 4);    // right <- tmp
}

/* ----------------------------------------------------------------------------
    Local Functions - E Function Bit Selection
*/

// perform the E bit selection function
static void e_bit_selection(uint8_t *out, uint8_t *in) {
	for (size_t bit_idx = 0; bit_idx < 48; bit_idx++) 
		get_bit(in, E_FN[bit_idx] - 1) ? set_bit(out, bit_idx) : reset_bit(out, bit_idx);
}

/* ----------------------------------------------------------------------------
    Local Functions - Selection Function 
*/

// wrapper around all 8 selection functions
static void select(uint8_t *out, uint8_t *in) {	
	select_s1(out, in);
	select_s2(out, in);
	select_s3(out, in);
	select_s4(out, in);
	select_s5(out, in);
	select_s6(out, in);
	select_s7(out, in);
	select_s8(out, in);
}

// selection function 1
static void select_s1(uint8_t *out, uint8_t *in) {
	// select 1: bits 0..5
	uint8_t s1 = ((in[0] & 0xFC) >> 2); 

	uint8_t row = get_row(s1);  
	uint8_t col = get_col(s1);
	uint8_t res = S1[row][col]; 

#ifdef TRACE
	trace_sbox(S1, "S-BOX 1:", s1, row, col, res); 
#endif 

	out[0] |= (res << 4) & 0xF0; 
}

// selection function 2
static void select_s2(uint8_t *out, uint8_t *in) {
	// select 2: bits 6..11
	uint8_t s2 = ((in[0] & 0x03) << 4) | ((in[1] & 0xF0) >> 4); 

	uint8_t row = get_row(s2);  
	uint8_t col = get_col(s2);
	uint8_t res = S2[row][col]; 

#ifdef TRACE
	trace_sbox(S2, "S-BOX 2:", s2, row, col, res); 
#endif 

	out[0] |= res;  
}

// selection function 3
static void select_s3(uint8_t *out, uint8_t *in) {
	// select 3: bits 12..17
	uint8_t s3 = ((in[1] & 0x0F) << 2) | ((in[2] & 0xC0) >> 6);

	uint8_t row = get_row(s3);  
	uint8_t col = get_col(s3);
	uint8_t res = S3[row][col]; 

#ifdef TRACE
	trace_sbox(S3, "S-BOX 3:", s3, row, col, res); 
#endif 

	out[1] |= (res << 4);
}

// selection function 4
static void select_s4(uint8_t *out, uint8_t *in) {
	// select 4: bits 18..23
	uint8_t s4 = (in[2]  & 0x3F);     

	uint8_t row = get_row(s4);  
	uint8_t col = get_col(s4);
	uint8_t res = S4[row][col]; 

#ifdef TRACE
	trace_sbox(S4, "S-BOX 4:", s4, row, col, res); 
#endif 

	out[1] |= res;                            
}

// selection function 5
static void select_s5(uint8_t *out, uint8_t *in) {
	// select 5: bits 24..29
	uint8_t s5 = ((in[3] & 0xFC) >> 2);    

	uint8_t row = get_row(s5);  
	uint8_t col = get_col(s5);
	uint8_t res = S5[row][col]; 

#ifdef TRACE
	trace_sbox(S5, "S-BOX 5:", s5, row, col, res); 
#endif  

	out[2] |= (res << 4);                    
}

// selection function 6
static void select_s6(uint8_t *out, uint8_t *in) {
	// select 6: bits 30..35
	uint8_t s6 = ((in[3] & 0x03) << 4) | ((in[4] & 0xF0) >> 4);

	uint8_t row = get_row(s6);  
	uint8_t col = get_col(s6);
	uint8_t res = S6[row][col]; 

#ifdef TRACE
	trace_sbox(S6, "S-BOX 6:", s6, row, col, res); 
#endif  

	out[2] |= res;  
}

// selection function 7
static void select_s7(uint8_t *out, uint8_t *in) {
	// select 7: bits 36..41
	uint8_t s7 = ((in[4] & 0x0F) << 2) | ((in[5] & 0xC0) >> 6);  

	uint8_t row = get_row(s7);  
	uint8_t col = get_col(s7);
	uint8_t res = S7[row][col]; 

#ifdef TRACE
	trace_sbox(S7, "S-BOX 7:", s7, row, col, res); 
#endif 

	out[3] |= (res << 4);
}

// selection function 8
static void select_s8(uint8_t *out, uint8_t *in) {
	// select 8: bits 42..47
	uint8_t s8 = (in[5]  & 0x3F);  
	uint8_t row = get_row(s8);  
	uint8_t col = get_col(s8);
	uint8_t res = S8[row][col]; 

#ifdef TRACE
	trace_sbox(S8, "S-BOX 8:", s8, row, col, res); 
#endif  

	out[3] |= res;                           
}

/* ----------------------------------------------------------------------------
    Local Functions - Permutation Function 
*/

// permutation function
static void permute(uint8_t *out, uint8_t *in) {
	for (size_t bit_idx = 0; bit_idx < 32; bit_idx++) 
		get_bit(in, P_FN[bit_idx] - 1) ? set_bit(out, bit_idx) : reset_bit(out, bit_idx); 
}

/* ----------------------------------------------------------------------------
    Local Functions - Helpers
*/

// extract column index from byte:
// by DES spec: XXXCCCCX -> 0000CCCC
static uint8_t get_col(uint8_t byte) {
	return ((byte & 0x1E) >> 1); 
}

// extract row index from byte:
// by DES spec: XXRXXXXR -> 000000RR
static uint8_t get_row(uint8_t byte) {
	// hacky way to isolate non-contiguous bits in byte
	// it is clear from such solutions that DES was not optimized for software
	return (byte & 0x21) > 30 ? (byte & 0x21) - 30 : (byte & 0x21);
}

// helper function for printing trace information
static void trace_sbox(const uint8_t sbox[4][16], const char *str,
					   uint8_t in, uint8_t row, uint8_t col, uint8_t out) {
	printf("%-20s", str);
	bitdump(in, 6);
	printf(" (%d,%2d)", row, col);
	printf(" -> ");
	bitdump(out, 4);
	putchar('\n'); 
}
