// perm.h
// Permutation and Inverse Permutation. 

#ifndef __DES_PERM_H
#define __DES_PERM_H

/*
 * ip 
 * Perform cipher initial permutation. 
 *
 * Arguments:
 *	in  - input buffer
 *  out - output buffer
 */
void ip(uint8_t *in, uint8_t *out);

/*
 * inv_ip
 * Perform cipher final permutation. 
 *
 * Arguments:
 *	in  - input buffer
 *  out - output buffer
 */
void inv_ip(uint8_t *in, uint8_t *out);

#endif // __DES_PERM_H
