// vigenere.h
// Vigenere cipher implementation.

#ifndef __VIGENERE_H
#define __VIGENERE_H

/* ----------------------------------------------------------------------------
    Exported Functions
*/

/*
 * vigenere
 * Encipher / decipher bytes with vigenere.
 *
 * Arguments:
 *  dst  - destination message (output) buffer
 *  src  - source message (input) buffer
 *  mlen - message buffer length, in bytes
 *  key  - key (input) buffer
 *  klen - key buffer length, in bytes
 *
 * Returns:
 *  0 on success
 *  1 on failure
 */
int vigenere(uint8_t *dst, uint8_t *src, size_t mlen, uint8_t *key, size_t klen);

#endif // __VIGENERE_H
