 // rc4.c
// RC4 stream cipher implementation. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "rc4.h"

// cipher internal state size, in bytes
#define STATE_SIZE 256

int rc4(uint8_t *ct, uint8_t *pt, size_t plen, uint8_t *key, size_t klen) {
	// internal state buffer
	uint8_t s[STATE_SIZE];

	// rc4 key schedule
	rc4_ks(s, key, klen);

	uint8_t tmp;
	size_t i = 0;
	size_t j = 0;
	for (size_t b = 0; b < plen; b++) {
		i = (i + 1)    % STATE_SIZE;
		j = (j + s[i]) % STATE_SIZE;

		// transform the internal state
		tmp  = s[i];
		s[i] = s[j];
		s[j] = tmp;

		// do the encryption / decryption
		ct[b] = pt[b] ^ s[(s[i] + s[j]) % STATE_SIZE];
	}

	return 0;	
}

// generate <nbytes> bytes of rc4 keystream
int rc4_stream(uint8_t *buf, size_t nbytes, uint8_t *key, size_t klen) {
	// internal state buffer
	uint8_t s[STATE_SIZE];

	// rc4 key schedule
	rc4_ks(s, key, klen);

	uint8_t tmp;
	size_t i = 0;
	size_t j = 0;
	for (size_t b = 0; b < nbytes; b++) {
		i = (i + 1)    % STATE_SIZE;
		j = (j + s[i]) % STATE_SIZE;

		// transform the internal state
		tmp  = s[i];
		s[i] = s[j];
		s[j] = tmp;

		// generate the keystream byte
		buf[b] = s[(s[i] + s[j]) % STATE_SIZE];
	}

	return 0;
}

// rc4 key schedule
int rc4_ks(uint8_t *s, uint8_t *key, size_t keylen) {
	// set state vector s to s[0] = 0 ... s[255] = 255
	for (size_t i = 0; i < STATE_SIZE; i++) 
		s[i] = (uint8_t) i;

	uint8_t tmp;
	size_t j = 0;
	for (size_t i = 0; i < STATE_SIZE; i++) {
		j = (j + s[i] + key[i % keylen]) % STATE_SIZE;
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}

	return 0;
}
