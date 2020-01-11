// chacha20.h
// Implementation of the Chacha20 stream cipher. 

#ifndef __CHACHA_H
#define __CHACHA_H

/*
 * chacha20_cipher
 * Encrypt / decrypt data with chacha20 stream cipher. 
 *
 * Arguments:
 *	ct    - ciphertext buffer (output), <mlen> bytes
 *	pt    - plaintext buffer (input), <mlen> bytes
 *	mlen  - size of the the plaintext buffer in bytes
 *	key   - key buffer (input), 32 bytes
 *	nonce - nonce buffer (input), 12 bytes
 *	ctr   - initial block counter value 
 *
 * Returns:
 *	0 on success
 *	1 on error
 */
int chacha20_cipher(uint8_t *ct,  uint8_t *pt,    size_t mlen, 
					uint8_t *key, uint8_t *nonce, uint32_t ctr);

/*
 * chacha20_core
 * Compute the chacha20 core function. 
 *
 * Arguments:
 *	block - keystream block buffer (output), 64 bytes
 *	key   - key buffer (input), 32 bytes
 *	nonce - nonce buffer (input), 12 bytes
 *	ctr   - block counter value
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int chacha20_core(uint8_t *block, uint8_t *key, uint8_t *nonce, uint32_t ctr);

#endif // __CHACHA_H
