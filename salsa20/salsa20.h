// salsa20.h
// Implementation of the Salsa20 stream cipher.

#ifndef __SALSA_H
#define __SALSA_H

/* ----------------------------------------------------------------------------
	Exported Functions
*/

/*
 * salsa20
 * Encipher / decipher via the salsa20 stream cipher. 
 *
 * Arguments:
 *	out   - output buffer, <mlen> bytes
 *	in    - input buffer, <mlen> bytes
 *	mlen  - length of the message <in> to which keystream is applied
 *	key   - key buffer, 32 bytes
 *	nonce - nonce buffer, 8 bytes
 *
 * Returns:
 *	0 on success
 *	1 on error
 */
int salsa20(uint8_t *out, uint8_t *in, size_t mlen, uint8_t *key, uint8_t *nonce);

/*
 * salsa20_core
 * Compute the salsa20 core function. 
 *
 * Arguments:
 *	block - output buffer for keystream block, 64 bytes
 *	key   - key buffer, 32 bytes
 *	nonce - nonce buffer, 8 bytes
 *	ctr   - current counter value [0,2^64-1]
 */
void salsa20_core(uint8_t *block, uint8_t *key, uint8_t *nonce, uint64_t ctr);

/*
 * salsa20_hash
 * Compute the salsa20 'hash' function. 
 *
 * Arguments:
 *	out - output buffer, 64 bytes
 *	in  - input buffer, 64 bytes
 */
void salsa20_hash(uint8_t *out, uint8_t *in);

#endif // __SALSA_H

