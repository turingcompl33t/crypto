// sub_bytes.h
// Byte substitution via S-Boxes.

#ifndef __AES_SUB_BYTES_H
#define __AES_SUB_BYTES_H

/* ----------------------------------------------------------------------------
	Global Functions 
*/

/*
 * sub_bytes
 * Perform byte substitution via S-Box. 
 *
 * Arguments:
 *	state - pointer to state matrix 
 */
void sub_bytes(uint8_t *state);

/*
 * inv_sub_bytes
 * Perform byte substitution via inverse S-Box. 
 *
 * Arguments:
 *	state - pointer to state matrix 
 */
void inv_sub_bytes(uint8_t *state);

/*
 * sub_byte
 * Perform byte substitution via S-Box.
 *
 * Arguments:
 *	byte - input byte
 *
 * Returns:
 *	result of byte substitution
 */
uint8_t sub_byte(uint8_t byte);

/*
 * inv_sub_byte
 * Perform byte substitution via inverse S-Box.
 *
 * Arguments:
 *	byte - input byte
 *
 * Returns:
 *	result of byte substitution
 */
uint8_t inv_sub_byte(uint8_t byte); 

#endif // __AES_SUB_BYTES_H
