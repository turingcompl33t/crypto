// des.h
// Data Encryption Standard cipher implementation. 

#ifndef __DES_H
#define __DES_H

/*
 * des_encrypt
 * Perform DES encryption. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer, 8 bytes
 *	pt  - plaintext (input) buffer, 8 bytes
 *	key - key (input) buffer, 8 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int des_encrypt(uint8_t *ct, uint8_t *pt, uint8_t *key);

/*
 * des_decrypt
 * Perform DES decryption. 
 *
 * Arguments:
 *	pt  - plaintext (output) buffer, 8 bytes
 *	ct  - ciphertext (input) buffer, 8 bytes
 *	key - key (input) buffer, 8 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int des_decrypt(uint8_t *pt, uint8_t *ct, uint8_t *key);

/*
 * des3_encrypt
 * Perform 3DES encryption. 
 *
 * Arguments:
 *	ct  - ciphertext (output) buffer, 8 bytes
 *	pt  - plaintext (input) buffer, 8 bytes
 *	key1 - key 1 (input) buffer, 8 bytes
 *	key2 - key 2 (input) buffer, 8 bytes
 *	key3 - key 3 (input) buffer, 8 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int des3_encrypt(uint8_t *ct, uint8_t *pt, uint8_t *k1, uint8_t *k2, uint8_t *k3);

/*
 * des3_decrypt
 * Perform 3DES decryption. 
 *
 * Arguments:
 *	pt   - plaintext (output) buffer, 8 bytes
 *	ct   - ciphertext (input) buffer, 8 bytes
 *	key1 - key 1 (input) buffer, 8 bytes
 *	key2 - key 2 (input) buffer, 8 bytes
 *	key3 - key 3 (input) buffer, 8 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int des3_decrypt(uint8_t *pt, uint8_t *ct, uint8_t *k1, uint8_t *k2, uint8_t *k3);

#endif // _DES_H
