// feistel.h
// Cipher feistel network. 

#ifndef __DES_FEISTEL_H
#define __DES_FEISTEL_H

/*
 * feistel
 * Perform single iteration of feistel network. 
 *
 * Arguments:
 *	state  - internal state buffer
 *	subkey - round subkey
 */
void feistel(uint8_t *state, uint8_t *subkey);

/*
 * cipher_f
 * Apply the DES f-function to r and round subkey:
 * 	r_next <- f(r, k_n)
 *
 * Arguments:
 *	r_next - output buffer, 32 bits
 *	r      - input data buffer, 32 bits
 *	subkey - input key buffer, 48 bits
 */
void cipher_f(uint8_t *r_next, uint8_t *r, uint8_t *subkey);

/*
 * swap_halves
 * Swap the left and right halves of internal cipher state. 
 *
 * Arguments:
 *	state - 32-bit internal state buffer
 */
void swap_halves(uint8_t *state); 

#endif // __DES_FEISTEL_H
