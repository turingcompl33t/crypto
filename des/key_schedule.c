// key_schedule.c
// Key schedule generation. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"
#include "const.h"

/* ----------------------------------------------------------------------------
    Local Constants 
*/

// map round number -> number of bits left shifted
static const int LSHIFT_MAP[] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// permuted choice 1
static const int PC1_MAP[] = {
	57, 49, 41, 33, 25, 17, 9,
	1,  58, 50, 42, 34, 26, 18,
	10, 2,  59, 51, 43, 35, 27,
	19, 11, 3,  60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7,  62, 54, 46, 38, 30, 22,
	14, 6,  61, 53, 45, 37, 29,
	21, 13, 5,  28, 20, 12, 4
};

// permuted choice 2 
static const int PC2_MAP[] = {
	14, 17, 11, 24, 1,  5,
	3,  28, 15, 6,  21, 10,
	23, 19, 12, 4,  26, 8,
	16, 7,  27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};

/* ----------------------------------------------------------------------------
    Local Protypes 
*/

void lshiftd(uint8_t *state, size_t shift);
void lshiftc(uint8_t *state, size_t shift);

void pc1(uint8_t *key,   uint8_t *state);
void pc2(uint8_t *state, uint8_t *key_schedule);

/* ----------------------------------------------------------------------------
    Global Functions
    See module header file (des.h) for detailed function comments. 
*/

// expand key via key schedule algorithm
void expand_key(uint8_t *key, uint8_t *key_schedule) {
    // buffer for intermediate key calculations
    // bits 0..27  -> C
    // bits 28..55 -> D
    uint8_t state[DES_EFFECTIVE_KEYLEN_BYTES];
    
    // perform initial permutation
    pc1(key, state);

    // iterate 16 rounds, generate subkey for each round
    for (size_t round = 0; round < DES_NROUNDS; round++) {
        // left shift C block
        lshiftc(state, LSHIFT_MAP[round]);
        // left shift D block
        lshiftd(state, LSHIFT_MAP[round]);
        // perform permuted choice 2 and update key schedule
        pc2(state, key_schedule + (round * DES_SUBKEY_SIZE_BYTES));
    }
}

/* ----------------------------------------------------------------------------
    Local Functions 
*/

// left shift block C by <shift> bits
void lshiftc(uint8_t *state, size_t shift) {
    size_t bit_idx;
    uint8_t buffer[7];
    
    // result of left shift written to buffer
    for (bit_idx = 0; bit_idx < 28; bit_idx++) {
        get_bit(state, (bit_idx + shift) % 28) ? set_bit(buffer, bit_idx) : reset_bit(buffer, bit_idx);
    }

    // now write result of left shift to state
    for (bit_idx = 0; bit_idx < 28; bit_idx++) {
        get_bit(buffer, bit_idx) ? set_bit(state, bit_idx) : reset_bit(state, bit_idx);
    }
}

// left shift block D by <shift> bits
void lshiftd(uint8_t *state, size_t shift) {
    size_t bit_idx;
    uint8_t buffer[7];
    
    // result of left shift written to buffer
    for (bit_idx = 0; bit_idx < 28; bit_idx++) {
        get_bit(state, 28 + ((bit_idx + shift) % 28)) ? set_bit(buffer, 28 + bit_idx) : reset_bit(buffer, 28 + bit_idx);
    }

    // now write result of left shift to state
    for (bit_idx = 0; bit_idx < 28; bit_idx++) {
        get_bit(buffer, 28 + bit_idx) ? set_bit(state, 28 + bit_idx) : reset_bit(state, 28 + bit_idx);
    }
}

// perform permuted choice 1
void pc1(uint8_t *key, uint8_t *state) {
    // iterate over each bit in the intermediate key buffer
    for (size_t bit_idx = 0; bit_idx < DES_EFFECTIVE_KEYLEN_BITS; bit_idx++) {
        // populate with bit from original via via initial permutation mapping
        // if mapped bit = 1 -> set bit in intermediate
        // if mapped bit = 0 -> reset bit in intermediate
        get_bit(key, PC1_MAP[bit_idx] - 1) ? set_bit(state, bit_idx) : reset_bit(state, bit_idx);
    }
}

// perform permuted choice 2, update key schedule with round subkey
void pc2(uint8_t *state, uint8_t *key_schedule) {
    size_t bit_idx;
    // iterate over bits in key schedule subkey for this round
    for (bit_idx = 0; bit_idx < DES_SUBKEY_SIZE_BITS; bit_idx++) {
        // get the bit from current state, according to PC2 mapping
        // bit = 1 -> set bit in schedule subkey
        // bit = 0 -> reset bit in schedule subkey
        get_bit(state, PC2_MAP[bit_idx] - 1) ? set_bit(key_schedule, bit_idx) : reset_bit(key_schedule, bit_idx); 
    }
}

