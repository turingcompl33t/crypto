// mul.c 
// Finite-field multiplication utilities for AES implementation. 

#include <stdint.h>

#include "mul.h"
#include "const.h"

/* ----------------------------------------------------------------------------
	Global Functions
	See module header file (mul.h) for detailed function comments.
*/

// perform finite field multiplication
uint8_t ffmul(uint8_t op_a, uint8_t op_b) {
	// intermediate value contains stateful result 
	// multiplication done in discrete stages 
	uint8_t intermediate = 0x00; 

	// for each term of increasing degree in op_b
	for (int shift = 0; shift < 8; shift++) {
		// if the coefficient on this term is nonzero
		if ((op_b >> shift) & 0x01) {
			// xor in result of multiplication of op_a by that term
			intermediate = intermediate ^ ixmul(op_a, shift);
		}
	}

	return intermediate;
}

// perform iterative multiplication of polynomial by 'x'
uint8_t ixmul(uint8_t operand, int niter) {
	uint8_t intermediate = operand;
	for (int i = 0; i < niter; i++) {
		intermediate = xmul(intermediate);
	}
	return intermediate; 
}

// perform multiplication of polynomial by 'x'
uint8_t xmul(uint8_t operand) {
	// if b7 coefficient will be 1 after multiplication, reduce modulo aes polynomial
	// otherwise result is already in reduced form, no further computation needed
	return ((operand & 0x80) >> 7) ? ((operand << 1) ^ AES_POLY) : (operand << 1);
}
