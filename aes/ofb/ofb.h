// ofb.h
// Perform AES encryption / decryption in OFB mode. 

#ifndef __AES_OFB_H
#define __AES_OFB_H

/*
 * aes_128_ofb_cipher
 * Run 128-bit AES in OFB mode to encrypt / decrypt bytes.
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - source length, in bytes
 *	key    - key buffer, 16 bytes
 *	iv     - initialization vector buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_128_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv);

/*
 * aes_192_ofb_cipher
 * Run 192-bit AES in OFB mode to encrypt / decrypt bytes.
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - source length, in bytes
 *	key    - key buffer, 24 bytes
 *	iv     - initialization vector buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_192_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv);

/*
 * aes_256_ofb_cipher
 * Run 256-bit AES in OFB mode to encrypt / decrypt bytes.
 *
 * Arguments:
 *	dst    - destination (output) buffer
 *	src    - source (input) buffer
 *	nbytes - source length, in bytes
 *	key    - key buffer, 32 bytes
 *	iv     - initialization vector buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on error 
 */
int aes_256_ofb_cipher(uint8_t *dst, uint8_t *src, size_t nbytes, uint8_t *key, uint8_t *iv);

#endif // __AES_OFB_H
