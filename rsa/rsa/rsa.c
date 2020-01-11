// rsa.c
// Implementation of RSA algorithm. 

#include <stdio.h>
#include <stdlib.h>

#include "rsa.h"

// the bignums library 
#include "../../bignum/bignum.h"

int rsa_keygen(bn_t *n, bn_t *e, bn_t *d, RSA_MODSIZE_T modsize) {
	return 0;
}

int rsa_encrypt(bn_t *ct, bn_t *pt, bn_t *e, bn_t *n) {
	return 0;
}	

int rsa_decrypt(bn_t *pt, bn_t *ct, bn_t *d, bn_t *n) {
	return 0; 
}
