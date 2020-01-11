// cipher.c
// Test program for the MT stream cipher. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mt.h"

/* ----------------------------------------------------------------------------
	Local Prototypes 
*/

static void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
	Main 
*/

int main(void) {
	uint16_t key = 0xFFAA;
	uint8_t pt[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99 };
	uint8_t ct[10];
	uint8_t nt[10];

	// encrypt / decrypt
	mt_cipher(ct, pt, 10, key);
	mt_cipher(nt, ct, 10, key);

	// how did we do?
	printf("key = %04x\n", key);
	puts("plaintext in:");
	hexdump(pt, 10);
	puts("ciphertext:");
	hexdump(ct, 10);
	puts("plaintext out:");
	hexdump(nt, 10);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions 
*/

static void hexdump(uint8_t *bytes, size_t len) {
	for (size_t i = 0; i < len; i++) 
		printf("%02x ", bytes[i]);
	putchar('\n');
}
