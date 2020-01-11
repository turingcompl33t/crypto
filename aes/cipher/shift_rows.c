// shift_rows.c
// ShiftRows cipher sub-operation implementation. 

#include <stdlib.h>
#include <stdint.h>

#include "util.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

void shift_row(uint8_t *state, size_t row);
void inv_shift_row(uint8_t *state, size_t row);

/* ----------------------------------------------------------------------------
	Global Functions
	See module header file (shift_rows.h) for detailed function comments. 
*/

// perform ShiftRows cipher sub-operation
void shift_rows(uint8_t *state) {
	// for each row in state 
	for (size_t row = 0; row < 4; row++) {
		// shift it 
		shift_row(state, row);
	}
}

// perform InvShiftRows cipher sub-operation
void inv_shift_rows(uint8_t *state) {
	// for each row in state 
	for (size_t row = 0; row < 4; row++) {
		// shift it 
		inv_shift_row(state, row); 
	}
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// shift an individual row
void shift_row(uint8_t *state, size_t row) {
	uint8_t new[4];
	// locally buffer the new row 
	// ('row' is also the shift amount)
	new[0] = mget(state, row, (0 + row) % 4);
	new[1] = mget(state, row, (1 + row) % 4); 
	new[2] = mget(state, row, (2 + row) % 4);
	new[3] = mget(state, row, (3 + row) % 4);

	// set the new row buffer in state
	for (size_t col = 0; col < 4; col++) {
		mset(state, row, col, new[col]);
	}
}

// inverse shift an individual row
void inv_shift_row(uint8_t *state, size_t row) {
	uint8_t new[4];
	// locally buffer the new row
	// ('row' is also shift amount)
	new[0] = mget(state, row, (0 - row) % 4);
	new[1] = mget(state, row, (1 - row) % 4);
	new[2] = mget(state, row, (2 - row) % 4);
	new[3] = mget(state, row, (3 - row) % 4);

	// set the new row buffer in state
	for (size_t col = 0; col < 4; col++) {
		mset(state, row, col, new[col]);
	}
}
