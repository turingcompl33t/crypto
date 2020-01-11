// util.c
// Utility functions. 

#include <stdio.h>
#include <stdint.h>

#include "util.h"

/* ----------------------------------------------------------------------------
    Global Functions
    See module header file (des.h) for detailed function comments. 
*/

// get bit at index <bit_idx> from <src> buffer
int get_bit(uint8_t *src, int bit_idx) {
    int byte_idx = bit_idx / 8;
    int bit_offset = bit_idx % 8;

    uint8_t byte = src[byte_idx];
    uint8_t mask = 0x80 >> bit_offset;

    return ((byte & mask) >> (7 - bit_offset));
}

// set bit at index <bit_idx> from <src> buffer 
void set_bit(uint8_t *dst, int bit_idx) {
    int byte_idx = bit_idx / 8;
    int bit_offset = bit_idx % 8;

    uint8_t mask = 0x80 >> bit_offset;

    dst[byte_idx] |= mask;
}

// set bit at index <bit_idx> from <src> buffer 
void reset_bit(uint8_t *dst, int bit_idx) {
    int byte_idx = bit_idx / 8;
    int bit_offset = bit_idx % 8;

    uint8_t mask = ~(0x80 >> bit_offset);

    dst[byte_idx] &= mask;
}

// perform bitwise XOR of arbitrary sized data blocks 
void xor_blocks(uint8_t *dst, uint8_t *src_a, uint8_t *src_b, size_t nblocks) {
    for (size_t i = 0; i < nblocks; i++) {
        dst[i] = (src_a[i] ^ src_b[i]);
    }
}

// print hexadecimal formatted bytes 
void hexdump(uint8_t *bytes, size_t len) {
    for (size_t i = 0; i < len; i++)
        printf("%02x ", bytes[i]);
    putchar('\n');
}

// print <nbits> low order bits of byte
void bitdump(uint8_t byte, size_t nbits) {
    char bit;
    uint8_t mask = 0x80 >> (8 - nbits);
    for (int i = (8 - nbits); i < 8; i++) {
        bit = (byte & mask) == 0 ? '0' : '1';
        putchar(bit);
        mask >>= 1;
    }
}
