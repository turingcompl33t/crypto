// mul.h
// Finite-field multiplication utilities for AES implementation. 

#ifndef __AES_MUL_H
#define __AES_MUL_H

/* ----------------------------------------------------------------------------
	Global Functions
*/

/*
 * ffmul
 * Perform finite field multiplication. 
 *
 * Polynomial multiplication within the finite field, 
 * in this context, refers to polynomial multiplication 
 * modulo the AES standard irreducible polynomial, m(x). 
 *
 * Arguments:
 *	op_a - first operand
 *	op_b - second operand 
 *
 * Returns:
 *	result of finite field multiplication 
 */
uint8_t ffmul(uint8_t op_a, uint8_t op_b);

/*
 * ixmul
 * Perform iterative multiplication of polynomial by 'x'.
 *
 * Arguments
 * operand - the input polynomial
 * niter   - number of times polynomial should be multiplied by 'x'
 *
 * Result:
 *	result of iterative multiplication of polynomial 
 */
uint8_t ixmul(uint8_t operand, int niter);

/*
 * xmul
 * Perform multiplication of polynomial by 'x'.
 *
 * Arguments:
 *	operand - the input polynomial
 *
 * Returns:
 *	result of multiplication 
 */
uint8_t xmul(uint8_t operand);

#endif // __AES_MUL_H
