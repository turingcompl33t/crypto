// test.c
// Test program for AES in CTR mode. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "ctr.h"

#define NBYTES 32

static void hexdump(uint8_t *bytes, size_t len); 

int main(void) {
	// key: 16 bytes 
	uint8_t key[]  = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	// nonce: 16 bytes 
	uint8_t nonce[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	
	// plaintext: 32 bytes 
	uint8_t pt[]  = {
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34,
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
	};

	uint8_t ct[NBYTES];  // intermediary ciphertext 
	uint8_t nt[NBYTES];  // the "newtext", output of final decryption

	// run CTR mode twice, once for 'encryption' and again for 'decryption'
	aes_128_ctr_cipher(ct, pt, NBYTES, key, nonce);
	aes_128_ctr_cipher(nt, ct, NBYTES, key, nonce);

	// how did we do?
	puts("key:");
	hexdump(key, 16);

	puts("plaintext in:");
	hexdump(pt, NBYTES);

	puts("ciphertext:");
	hexdump(ct, NBYTES);

	puts("plaintext out:");
	hexdump(nt, NBYTES);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// dump hex-formatted bytes to stdout
static void hexdump(uint8_t *bytes, size_t len) {
	for (size_t i = 0; i < len; i++)
		printf("%02x ", bytes[i]);
	putchar('\n');
}
