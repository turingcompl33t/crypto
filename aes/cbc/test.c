// test.c
// Test program for AES in CBC mode. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cbc.h"

#define NBYTES 32

int main(void) {
	// key: 16 bytes for 128-bit AES
	uint8_t key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
	// iv: 16 bytes 
	uint8_t iv[]  = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	
	// plaintext: 32 bytes, 2x16 byte blocks
	uint8_t pt[]  = {
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34,
		0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34
	};

	uint8_t ct[NBYTES];  // intermediary ciphertext 
	uint8_t nt[NBYTES];  // the "newtext", output of final decryption

	aes_128_cbc_encrypt(ct, pt, NBYTES, key, iv);
	aes_128_cbc_decrypt(nt, ct, NBYTES, key, iv);

	// lets see how we did
	puts("key:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", key[i]);
	}
	putchar('\n'); 

	puts("iv:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", iv[i]);
	}
	putchar('\n'); 

	puts("plaintext in:");
	for (size_t i = 0; i < NBYTES; i++) {
		printf("%02x ", pt[i]); 
	}
	putchar('\n'); 

	puts("ciphertext:");
	for (size_t i = 0; i < NBYTES; i++) {
		printf("%02x ", ct[i]); 
	}
	putchar('\n'); 

	puts("plaintext out:");
	for (size_t i = 0; i < NBYTES; i++) {
		printf("%02x ", nt[i]); 
	}
	putchar('\n');

	return 0;
}
