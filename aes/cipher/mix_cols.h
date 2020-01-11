// mix_cols.h
// MixCols cipher sub-operation implementation.

#ifndef __AES_MIX_COLS_H
#define __AES_MIX_COLS_H

#include <stdint.h>

/* ----------------------------------------------------------------------------
	Global Functions
*/

/*
 * mix_cols 
 * Perform MixCols cipher sub-operation. 
 *
 * Arguments:
 *	state - pointer to internal state matrix
 */
void mix_cols(uint8_t *state);

/*
 * inv_mix_cols 
 * Perform InvMixCols cipher sub-operation. 
 *
 * Arguments:
 *	state - pointer to internal state matrix
 */
void inv_mix_cols(uint8_t *state);

#endif // __AES_MIX_COLS_H
