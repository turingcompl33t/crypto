// ctr.h
// Perform AES encryption / decryption in CTR mode.

#ifndef __AES_CTR_H
#define __AES_CTR_H

/*
 * aes_128_ctr_cipher
 * Run 128-bit AES in CTR mode to encrypt / decrypt bytes. 
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - plaintext length, in bytes
 *	key    - key buffer, 16 bytes
 *	nonce  - nonce buffer, 16 bytes 
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_128_ctr_cipher(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key, uint8_t *nonce);

/*
 * aes_192_ctr_cipher
 * Run 192-bit AES in CTR mode to encrypt / decrypt bytes. 
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - source length, in bytes
 *	key    - key buffer, 24 bytes
 *	nonce  - nonce buffer, 16 bytes 
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_192_ctr_cipher(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key, uint8_t *nonce);

/*
 * aes_256_ctr_cipher
 * Run 256-bit AES in CTR mode to encrypt / decrypt bytes. 
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - source length, in bytes
 *	key    - key buffer, 32 bytes
 *	nonce  - nonce buffer, 16 bytes 
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_256_ctr_cipher(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key, uint8_t *nonce);

#endif // __AES_CTR_H
