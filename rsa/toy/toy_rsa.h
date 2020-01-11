// toy_rsa.h
// "Toy" implementation of RSA using small numbers.
//
// Intended to cement understanding of the algo prior 
// to implementing with large numbers for actual security.

#ifndef __TOY_RSA_H
#define __TOY_RSA_H

/*
 * toy_rsa_keygen
 * Generate RSA public key (e, n), private key (d, n) pairs. 
 *
 * Arguments:
 *	ret_e - integer buffer for computed 'e' value
 *	ret_d - integer buffer for computed 'd' value 
 *	ret_n - integer buffer for computed 'n' value 
 *
 * Returns:
 *	0 on success
 *	1 on failure 
 */
int toy_rsa_keygen(unsigned int *ret_e, unsigned int *ret_d, unsigned int *ret_n); 

/*
 * toy_rsa_encrypt
 * Perform RSA encryption. 
 *
 * Arguments:
 *	ct - integer buffer for computer ciphertext 
 *	pt - integer plaintext 
 * 	e  - public key parameter 'e'
 *	n  - public key parameter 'n'
 */
int toy_rsa_encrypt(unsigned int *ct, unsigned int pt, unsigned int e, unsigned int n);

/*
 * toy_rsa_decrypt
 * Perform RSA decryption. 
 *
 * Arguments:
 *	pt - integer buffer for computed plaintext 
 *	ct - integer ciphertext 
 * 	d  - public key parameter 'd'
 *	n  - public key parameter 'n'
 */
int toy_rsa_decrypt(unsigned int *pt, unsigned int ct, unsigned int d, unsigned int n);

#endif // __TOY_RSA_H
