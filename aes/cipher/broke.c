// test.c
// Test program for vanilla AES cipher implementation.
// Inputs taken from FIPS 197. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "aes.h"

int main(void) {
	uint8_t key[] = {0x59, 0x45, 0x4c, 0x4c, 0x4f, 0x57, 0x20, 0x53, 0x55, 0x42, 0x4d, 0x41, 0x52, 0x49, 0x4e, 0x45};
	
	uint8_t pt1[]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t pt2[]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint8_t pt3[]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

	uint8_t ct1[16];
	uint8_t ct2[16]; 
	uint8_t ct3[16];   

	aes_128_encrypt(ct1, pt1, key);
	aes_128_encrypt(ct2, pt2, key);
	aes_128_encrypt(ct3, pt3, key); 

	puts("ciphertext 1:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", ct1[i]); 
	}
	putchar('\n'); 

	puts("ciphertext 2:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", ct2[i]); 
	}
	putchar('\n'); 

	puts("ciphertext 3:");
	for (size_t i = 0; i < 16; i++) {
		printf("%02x ", ct3[i]); 
	}
	putchar('\n'); 

	return 0;
}