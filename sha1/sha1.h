// sha1.h
// Implementation of the SHA-1 hash function.

#ifndef __SHA1_H
#define __SHA1_H

/*
 * sha1
 * Compute SHA-1 digest of message <message>.
 *
 * Arguments:
 *	digest  - output buffer for message digest 
 *	message - input buffer for message 
 *	len     - length of the input message (# bytes)
 */
void sha1(uint32_t *digest, uint8_t *message, size_t len); 

#endif // __SHA1_H
