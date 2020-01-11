// toy_test.c
// Test for "toy" implementation of RSA using small numbers.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "toy_rsa.h"

int main(void) {
	srand(1); 

	unsigned int e;
	unsigned int d;
	unsigned int n;

	// generate public and private keypair
	toy_rsa_keygen(&e, &d, &n);

	// verify what we got 
	puts("keygen results:");
	printf("e = %u\n", e);
	printf("d = %u\n", d);
	printf("n = %u\n", n);

	unsigned int pt = 42;  // secret to life, universe, everything
						   // must be kept SECURE 
	unsigned int ct;       // buffer for ciphertext
	unsigned int nt;       // buffer for 'newtext', post decryption

	// encrypt with public key
	toy_rsa_encrypt(&ct, pt, e, n);

	// decrypt with secret key
	toy_rsa_decrypt(&nt, ct, d, n); 

	// how did we do?
	puts("encrytion / decryption results:");
	printf("pt = %u\n", pt);
	printf("ct = %u\n", ct);
	printf("nt = %u\n", nt); 

	return 0;
}
