// aes.h
// AES algorithm implementation. 

#ifndef __AES_H
#define __AES_H

/* ----------------------------------------------------------------------------
	AES 128
*/

/*
 * aes_128
 * Perform 128-bit AES encryption. 
 */
int aes_128_encrypt(uint8_t *out, uint8_t *in, uint8_t *key);

/*
 * aes_128
 * Perform 128-bit AES decryption. 
 */
int aes_128_decrypt(uint8_t *out, uint8_t *in, uint8_t *key);

/* ----------------------------------------------------------------------------
	AES 192
*/

/*
 * aes_192
 * Perform 192-bit AES encryption. 
 */
int aes_192_encrypt(uint8_t *out, uint8_t *in, uint8_t *key);

/*
 * aes_192
 * Perform 192-bit AES decryption. 
 */
int aes_192_decrypt(uint8_t *out, uint8_t *in, uint8_t *key);

/* ----------------------------------------------------------------------------
	AES 256
*/

/*
 * aes_256
 * Perform 256-bit AES encryption. 
 */
int aes_256_encrypt(uint8_t *out, uint8_t *in, uint8_t *key);

/*
 * aes_256
 * Perform 256-bit AES decryption. 
 */
int aes_256_decrypt(uint8_t *out, uint8_t *in, uint8_t *key);

#endif // __AES_H
