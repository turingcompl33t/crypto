// shift_rows.h
// ShiftRows cipher sub-operation implementation. 

#ifndef __AES_SHIFT_ROWS_H
#define __AES_SHIFT_ROWS_H

#include <stdint.h>

/* ----------------------------------------------------------------------------
	Global Functions
*/

/*
 * shift_rows
 * Perform ShiftRows cipher sub-operation. 
 *
 * Arguments:
 *	state - pointer to internal state matrix 
 */
void shift_rows(uint8_t *state);

/*
 * inv_shift_rows
 * Perform InvShiftRows cipher sub-operation. 
 *
 * Arguments:
 *	state - pointer to internal state matrix 
 */
void inv_shift_rows(uint8_t *state);

#endif // __AES_SHIFT_ROWS_H
