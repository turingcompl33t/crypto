// auth.h 
// Cryptographic message authentication primitives. 

#ifndef __CRYPTO_AUTH_H
#define __CRYPTO_AUTH_H

#include <stdbool.h>

/* ----------------------------------------------------------------------------
	Exported Functions
*/

/*
 * auth_cmac_gen
 * Compute CMAC Message Authentication Code. 
 *
 * Arguments:
 *	tag  - MAC tag (output) buffer
 *	msg  - message (input) buffer, arbitrary length 
 *	mlen - length of the message buffer, in bytes
 *	key  - key (input) buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int auth_cmac_gen(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *key);

/*
 * auth_cmac_ver
 * Verify CMAC Message Authentication Code. 
 *
 * Arguments:
 *	msg  - message (input) buffer, arbitrary length 
 *	mlen - length of the message buffer, in bytes
 *	key  - key (input) buffer, 16 bytes
 *  tag  - received tag (input) buffer, 16 bytes
 *
 * Returns:
 * 	True on successful tag verifcation
 *	False otherwise
 */
bool auth_cmac_ver(uint8_t *msg, size_t mlen, uint8_t *key, uint8_t *tag);

/*
 * auth_ecbc
 * Compute encrypted CBC Message Authentication Code.
 * 
 * Arguments:
 *	tag  - MAC tag (output) buffer, 16 bytes
 *	msg  - message (input) buffer, arbitrary length
 *	mlen - length of the message buffer, in bytes
 *	k1   - key 1 (input) buffer, 16 bytes
 *	k2   - key 2 (input) buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int auth_ecbc(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *k1, uint8_t *k2);

/*
 * auth_rawcbc
 * Compute raw CBC Message Authentication Code. 
 *
 * WARNING: raw CBC MAC is not EU_CMA secure;
 * DO NOT USE in isolation (see break_rawcbc.c)
 *
 * Arguments:
 *	tag  - MAC tag (output) buffer, 16 bytes
 *	msg  - message (input) buffer, arbitrary length
 *	mlen - length of the message buffer, in bytes
 *	key  - key (input) buffer, 16 bytes
 *
 * Returns:
 *	0 on success
 *	1 on failure
 */
int auth_rawcbc(uint8_t *tag, uint8_t *msg, size_t mlen, uint8_t *key);

#endif // __CRYPTO_AUTH_H
