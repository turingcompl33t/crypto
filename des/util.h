// util.h
// Utility functions.

#ifndef __DES_UTIL_H
#define __DES_UTIL_H

/*
 * get_bit
 * Get bit at index <bit_idx> from <src> buffer. 
 *
 * Arguments:
 *	src     - source buffer 
 *	bit_idx - index of bit to get
 */
int get_bit(uint8_t *src, int bit_idx);

// 
/*
 * set_bit
 * Set bit at index <bit_idx> from <src> buffer. 
 *
 * Arguments:
 * 	dst     - destination buffer
 * 	bit_idx - index of bit to set (1)
 */
void set_bit(uint8_t *dst, int bit_idx);

/*
 * reset_bit
 * Set bit at index <bit_idx> from <src> buffer. 
 *
 * Arguments:
 *	dst     - destination buffer
 *	bit_idx - index of bit to reset
 */
void reset_bit(uint8_t *dst, int bit_idx);

/*
 * xor_blocks
 * Perform bitwise XOR of arbitrary sized data blocks. 
 *
 * Intel syntax: dst <- src_a XOR src_b
 *
 * Arguments:
 * 	dst     - destination buffer
 *	src_a   - source buffer A
 *	src_b   - source buffer B
 *  nblocks - number of data blocks
 *
 */
void xor_blocks(uint8_t *dst, uint8_t *src_a, uint8_t *src_b, size_t nblocks);

/*
 * hexdump
 * Print a block of data in hexadecimal format to stdout. 
 *
 * Arguments:
 *	bytes - pointer to data block to print
 * 	len   - size of block to print, in bytes
 */
void hexdump(uint8_t *bytes, size_t len);

/*
 * bitdump
 */
void bitdump(uint8_t byte, size_t nbits);

#endif // __DES_UTIL_H
