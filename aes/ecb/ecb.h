// ecb.h
// Perform AES encryption / decryption in electronic codebook (ECB) mode. 

#ifndef __AES_ECB_H
#define __AES_ECB_H

/* ----------------------------------------------------------------------------
	AES 128 
*/

/*
 * aes_128_ecb_encrypt
 * Perform 128-bit AES encryption in ECB mode. 
 */
int aes_128_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key);

/*
 * aes_128_ecb_decrypt
 * Perform 128-bit AES decryption in ECB mode. 
 */
int aes_128_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key); 

/* ----------------------------------------------------------------------------
	AES 192
*/

/*
 * aes_192_ecb_encrypt
 * Perform 192-bit AES encryption in ECB mode. 
 */
int aes_192_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key);

/*
 * aes_192_ecb_decrypt
 * Perform 192-bit AES decryption in ECB mode. 
 */
int aes_192_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key); 

/* ----------------------------------------------------------------------------
	AES 256 
*/

/*
 * aes_256_ecb_encrypt
 * Perform 256-bit AES encryption in ECB mode. 
 */
int aes_256_ecb_encrypt(uint8_t *ct, uint8_t *pt, size_t nbytes, uint8_t *key);

/*
 * aes_256_ecb_decrypt
 * Perform 256-bit AES decryption in ECB mode. 
 */
int aes_256_ecb_decrypt(uint8_t *pt, uint8_t *ct, size_t nbytes, uint8_t *key); 

#endif // _AES_ECB_H
