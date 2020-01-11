// vigenere.c
// Vigenere cipher implementation.

#include <stdlib.h>
#include <stdint.h>

/* ----------------------------------------------------------------------------
    Exported Functions
    See module header file (vigenere.h) for detailed function comments. 
*/

// encipher / decipher bytes with vigenere
int vigenere(uint8_t *dst, uint8_t *src, size_t mlen, uint8_t *key, size_t klen) {
    size_t midx = 0;
    size_t kidx = 0;
    while (midx < mlen) {
        dst[midx] = src[midx] ^ key[kidx];
        midx++;
        kidx = (kidx + 1) % klen;
    }

    return 0;
}
