 // mt.h
// Mersenne Twister PRNG.

#ifndef __MT_H
#define __MT_H

/* ----------------------------------------------------------------------------
	Exported Types 
*/

// PRNG instance type
typedef struct mt {
	uint32_t *state;  // state vector
	size_t   idx;     // current index
} mt_t;

/* ----------------------------------------------------------------------------
	Exported Functions 
*/

/*
 * mt_seed 
 * Initialize the MT PRNG and seed with <seed>.
 * 
 * Arguments:
 *	mt   - mt prng instance
 *	seed - seed value for PRNG
 *
 * Returns:
 *	0 on success
 *	1 on failure (e.g. memory error)
 */
int mt_seed(mt_t *mt, uint32_t seed);

/*
 * mt_splice
 * Initialize the MT PRNG from existing state vector.
 *
 * Arguments:
 *	mt    - mt prng instance 
 *	state - state vector 
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int mt_splice(mt_t *mt, uint32_t *state);

/*
 * mt_rand
 * Extract a pseudorandom value in range [0, 2^32 - 1]
 *
 * Arguments:
 *	mt - mt prng instance 
 *
 * Returns:
 *	pseudorandom value in range [0, 2^32 - 1]
 */
uint32_t mt_rand(mt_t *mt);

/*
 * mt_cipher
 * Encrypt / decrypt data with the MT stream cipher. 
 *
 * Arguments:
 *	ct   - output buffer
 *	pt   - input buffer
 *	mlen - length of input buffer, in bytes
 *	key  - 16-bit encryption key
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int mt_cipher(uint8_t *ct, uint8_t *pt, size_t mlen, uint16_t key);

#endif // __MT_H
