 // rc4.h
// RC4 stream cipher implementation. 

#ifndef __RC4_H
#define __RC4_H

#include <stdint.h>

/*
 * rc4
 */
int rc4(uint8_t *ct, uint8_t *pt, size_t plen, uint8_t *key, size_t klen);

/*
 * rc4_stream
 */
int rc4_stream(uint8_t *buf, size_t nbytes, uint8_t *key, size_t klen);

/*
 * rc4_ks
 */
int rc4_ks(uint8_t *s, uint8_t *key, size_t keylen); 

#endif // __RC4_H
