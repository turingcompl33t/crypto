// cbc.c
// Perform AES encryption / decryption in cipher block-chaining (CBC) mode. 

#ifndef __AES_CBC_H
#define __AES_CBC_H

/* ----------------------------------------------------------------------------
	AES 128
*/

/*
 * aes_128_cbc_encrypt
 * Perform 128-bit AES encryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (16 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_128_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv);

/*
 * aes_128_cbc_decrypt
 * Perform 128-bit AES decryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (16 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_128_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv);

/* ----------------------------------------------------------------------------
	AES 192
*/

/*
 * aes_192_cbc_encrypt
 * Perform 192-bit AES encryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (24 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_192_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv);

/*
 * aes_192_cbc_decrypt
 * Perform 192-bit AES decryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (24 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_192_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv);

/* ----------------------------------------------------------------------------
	AES 256
*/

/*
 * aes_256_cbc_encrypt
 * Perform 256-bit AES encryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (32 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_256_cbc_encrypt(uint8_t *ct, uint8_t *pt, size_t len, uint8_t *key, uint8_t *iv);

/*
 * aes_256_cbc_decrypt
 * Perform 256-bit AES decryption in CBC mode. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer
 *	pt  - plaintext (input) buffer
 * 	len - size of plaintext, in bytes
 *	key - key buffer (32 bytes)
 *	iv  - initialization vector buffer (16 bytes)
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int aes_256_cbc_decrypt(uint8_t *pt, uint8_t *ct, size_t len, uint8_t *key, uint8_t *iv); 

#endif // __AES_CBC_H
