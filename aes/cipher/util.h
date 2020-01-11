// util.h
// Utility module for AES implementation. 

#ifndef __AES_UTIL_H
#define __AES_UTIL_H

#include <stdlib.h>
#include <stdint.h>

/* ----------------------------------------------------------------------------
	Global Functions
*/

/*
 * mget 
 * Get internal maxtrix element at (row, col).
 * Assumes 4x4, 16 element matrix represented as 1D array. 
 *
 * Arguments:
 *	m     - pointer to matrix object (1D array)
 * 	row   - row index
 *  col   - column index
 *
 * Returns:
 *	matrix element at (row, col)
 */
uint8_t mget(uint8_t *m, size_t row, size_t col);

/*
 * mset
 * Set internal matrix element at (row, col) to <val>.
 * Assumes 4x4, 16 element matrix represented as 1D array. 
 *
 * Arguments:
 *	m     - pointer to matrix object (1D array)
 * 	row   - row index
 *  col   - column index
 *	val   - new value to set 
 */
void mset(uint8_t *m, size_t row, size_t col, uint8_t val); 

/*
 * print_state
 * Print internal state to stdout. 
 *
 * Arguments:
 *	state - pointer to state matrix
 */
void print_state(uint8_t *state);

/*
 * print_word
 * Print a 32-bit word in hexadecimal format to stdout. 
 *
 * Arguments:
 *	word - pointer to 32-bit word
 */
void print_word(uint8_t *word);

#endif // __AES_UTIL_H
