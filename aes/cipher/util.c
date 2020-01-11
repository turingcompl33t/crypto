// util.c
// Utility module for AES implementation. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "util.h"

/* ----------------------------------------------------------------------------
	Global Functions
	See module header file (util.h) for detailed function comments. 
*/

// get internal matrix element at (row, col)
uint8_t mget(uint8_t *m, size_t row, size_t col) {
	return m[4*col + row];
}

// set internal matrix element at (row, col) to val
void mset(uint8_t *m, size_t row, size_t col, uint8_t val) {
	m[4*col + row] = val;
}


// print internal state to stdout 
void print_state(uint8_t *state) {
	if (!state)
		return;

	for (size_t row = 0; row < 4; row++) {
		for (size_t col = 0; col < 4; col++) {
			printf("%02x ", mget(state, row, col)); 
		}
		putchar('\n');
	}
}

// print 32-bit word in hexadecimal format to stdout
void print_word(uint8_t *word) {
	for (int i = 0; i < 4; i++) {
		printf("%02x", word[i]);
	}
	putchar('\n'); 
}


