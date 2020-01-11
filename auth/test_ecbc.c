// test_ecbc.c 
// Test program for ECBC MAC computation. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "auth.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	uint8_t k1[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	uint8_t k2[] = {0x01, 0x12, 0x23, 0x34, 0x45, 0x56, 0x67, 0x78, 0x89, 0x9A, 0xAB, 0xBC, 0xCD, 0xDE, 0xEF, 0xFF};

	uint8_t msg[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	uint8_t tag[16];

	auth_ecbc(tag, msg, 16, k1, k2);

	printf("TAG: ");
	hexdump(tag, 16);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// print hexadecimal-formatted bytes to stdout
static void hexdump(uint8_t *bytes, size_t len) {
	for (size_t i = 0; i < len; i++) 
		printf("%02x ", bytes[i]);
	putchar('\n');
}
