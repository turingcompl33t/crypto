// rsa.h
// Implementation of RSA algorithm.

#ifndef __RSA_H
#define __RSA_H

#include "../../bignum/bignum.h"

typedef enum {
	MOD_1024,  // 1024 bit modulus 
	MOD_2048,  // 2048 bit modulus 
	MOD_4096   // 4096 bit modulus 
} RSA_MODSIZE_T; 

/*
 * rsa_keygen 
 * Generate RSA public / private keypairs.
 *
 * Arguments:
 *	n       - prime modulus n (computed)
 *	e       - public exponent e (computed)
 *	d       - private exponent d (computed)
 *	modsize - size of the prime modulus n, in bits
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int rsa_keygen(bn_t *n, bn_t *e, bn_t *d, RSA_MODSIZE_T modsize); 

/*
 * rsa_encrypt
 * Perform RSA encryption: 
 *	encrypt ciphertext ct under public key (e, n)
 *
 * Arguments:
 *	ct - ciphertext value (computed)
 *	pt - plaintext value 
 *	e  - public exponent e
 *	n  - prime modulus n
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int rsa_encrypt(bn_t *ct, bn_t *pt, bn_t *e, bn_t *n);

/*
 * rsa_encrypt
 * Perform RSA decryption: 
 *	decrypt plaintext pt under private key (d, n)
 *
 * Arguments:
 *	pt - plaintext value (computed)
 *	ct - ciphertext value 
 *	d  - private exponent e
 *	n  - prime modulus n
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int rsa_decrypt(bn_t *pt, bn_t *ct, bn_t *d, bn_t *n);

#endif // __RSA_H
