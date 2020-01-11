// test.c
// Test program for vanilla AES cipher implementation.
// Inputs taken from FIPS 197. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "aes.h"

int main(void) {
	uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	uint8_t pt[]  = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

	uint8_t ct[16];  // intermediary ciphertext 
	uint8_t nt[16];  // the "newtext", output of final decryption

	aes_128_encrypt(ct, pt, key);
	aes_128_decrypt(nt, ct, key);

	puts("key:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", key[i]);
	}
	putchar('\n'); 

	puts("plaintext in:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", pt[i]); 
	}
	putchar('\n'); 

	puts("ciphertext:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", ct[i]); 
	}
	putchar('\n'); 

	puts("plaintext out:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", nt[i]); 
	}
	putchar('\n'); 

	return 0;
}
