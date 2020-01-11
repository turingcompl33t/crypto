// toy_rsa.c
// "Toy" implementation of RSA using small numbers.
//
// Intended to cement understanding of the algo prior
// to implementing with large numbers for actual security.

#include <stdio.h>
#include <stdlib.h>

#include "toy_rsa.h"

/* ----------------------------------------------------------------------------
	Local Constants
*/

// being lazy here and picking primes from prime table
static const int NPRIMES  = 4;
static const int PRIMES[] = { 3, 5, 7, 11 };

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

unsigned int toy_gcd(unsigned int o1, unsigned int o2);
unsigned int toy_invmod(unsigned int op, unsigned int mod);
unsigned int toy_modexp(unsigned int base, unsigned int exp, unsigned int mod);

/* ----------------------------------------------------------------------------
	Global Functions
	See module header file (toy_rsa.h) for detailed function comments.
*/

// generate RSA public key (e, n), private key (d, n) pairs
int toy_rsa_keygen(unsigned int *ret_e, unsigned int *ret_d, unsigned int *ret_n) {
	// choose primes p, q
	// question: what happens if p = q?
	unsigned int p = PRIMES[rand() % NPRIMES];
	unsigned int q = PRIMES[rand() % NPRIMES];

	// compute n = p*q
	unsigned int n = p*q;

	// compute totient function for n, phi(n)
	// (because n is product of primes, this is easy)
	unsigned int pn = (p-1)*(q-1);

	// choose e, must be relatively prime to phi(n)
	unsigned int e = 3;
	while (toy_gcd(pn, e) != 1)
		e++;

	// compute d as the multiplicative inverse of e modulo phi(n)
	unsigned int d = toy_invmod(e, pn);

	// return the key values
	*ret_e = e;
	*ret_d = d;
	*ret_n = n;

	return 0;
}

// perform RSA encryption
int toy_rsa_encrypt(unsigned int *ct, unsigned int pt, unsigned int e, unsigned int n) {
	*ct = toy_modexp(pt, e, n);
	return 0;
}

// perform RSA decryption
int toy_rsa_decrypt(unsigned int *pt, unsigned int ct, unsigned int d, unsigned int n) {
	*pt = toy_modexp(ct, d, n);
	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// compute modular multiplicative inverse
unsigned int toy_invmod(unsigned int op, unsigned int mod) {
	// extremely naive implementation
	// again: lazy, dont want to write extended euclidean algo twice
	for (unsigned int i = 1; i < mod; i++) {
		if ((op*i) % mod == 1)
			return i;
	}

	// this would be very bad, potentially word-ending
	return 0;
}

// compute the greatest common divisor (recursively)
unsigned int toy_gcd(unsigned int o1, unsigned int o2) {
	if (o1 % o2 == 0)
		return o2;
	else
		return toy_gcd(o2, o1 % o2);
}

// compute base^exp % mod
unsigned int toy_modexp(unsigned int base, unsigned int exp, unsigned int mod) {
	unsigned int res = 1;
	for (unsigned int i = exp; i > 0; i--)
		res = (res * base) % mod;
	return res;
}
