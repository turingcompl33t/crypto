// mix_cols.c
// MixCols cipher sub-operation implementation.

#include <stdint.h>
#include <stdlib.h>

#include "mul.h"
#include "util.h"
#include "mix_cols.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

void mix_col(uint8_t *state, size_t col);
void inv_mix_col(uint8_t *state, size_t col); 

/* ----------------------------------------------------------------------------
	Global Functions
	See module header file (mix_cols.h) for detailed function comments
*/

// perform MixCols cipher sub-operation
void mix_cols(uint8_t *state) {
	// for each column in state matrix
	for (size_t col = 0; col < 4; col++) {
		// mix it
		mix_col(state, col);
	}
}

// perform InvMixCols cipher sub-operation
void inv_mix_cols(uint8_t *state) {
	// for each column in state matrix
	for (size_t col = 0; col < 4; col++) {
		// mix it 
		inv_mix_col(state, col);
	}
}

/* ----------------------------------------------------------------------------
	Local Functions 
*/

// mix an individual column
void mix_col(uint8_t *state, size_t col) {
	uint8_t new[4];

	// who knew that matrix multiplication could be so... beautiful? 
	new[0] = ffmul(0x02, mget(state, 0, col)) ^ ffmul(0x03, mget(state, 1, col)) ^ mget(state, 2, col) ^ mget(state, 3, col);
	new[1] = mget(state, 0, col) ^ ffmul(0x02, mget(state, 1, col)) ^ ffmul(0x03, mget(state, 2, col)) ^ mget(state, 3, col);
	new[2] = mget(state, 0, col) ^ mget(state, 1, col) ^ ffmul(0x02, mget(state, 2, col)) ^ ffmul(0x03, mget(state, 3, col));
	new[3] = ffmul(0x03, mget(state, 0, col)) ^ mget(state, 1, col) ^ mget(state, 2, col) ^ ffmul(0x02, mget(state, 3, col));

	// write the buffered computation back to state matrix 
	for (size_t row = 0; row < 4; row++) {
		mset(state, row, col, new[row]);
	}
}

// inverse mix an individual column
void inv_mix_col(uint8_t *state, size_t col) {
	uint8_t new[4];

	// better than forward direction... or worse? 
	new[0] = ffmul(0x0e, mget(state, 0, col)) ^ ffmul(0x0b, mget(state, 1, col)) ^ ffmul(0x0d, mget(state, 2, col)) ^ ffmul(0x09, mget(state, 3, col));
	new[1] = ffmul(0x09, mget(state, 0, col)) ^ ffmul(0x0e, mget(state, 1, col)) ^ ffmul(0x0b, mget(state, 2, col)) ^ ffmul(0x0d, mget(state, 3, col));
	new[2] = ffmul(0x0d, mget(state, 0, col)) ^ ffmul(0x09, mget(state, 1, col)) ^ ffmul(0x0e, mget(state, 2, col)) ^ ffmul(0x0b, mget(state, 3, col));
	new[3] = ffmul(0x0b, mget(state, 0, col)) ^ ffmul(0x0d, mget(state, 1, col)) ^ ffmul(0x09, mget(state, 2, col)) ^ ffmul(0x0e, mget(state, 3, col));

	// write the buffered computation back to state matrix 
	for (size_t row = 0; row < 4; row++) {
		mset(state, row, col, new[row]); 
	}
}



