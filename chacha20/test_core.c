// test_core.c
// Test program for chacha20 core function. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "chacha20.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void dump_bytes(uint8_t *bytes, int n, int offset);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	uint8_t key[] = {
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
		0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
		0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
	};

	uint8_t nonce[] = {
		0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00
	};

	uint32_t ctr = 1;

	puts("[DEBUG] input key:");
	dump_bytes(key, 32, 0);
	puts("[DEBUG] input nonce:");
	dump_bytes(nonce, 12, 0);
	printf("[DEBUG] input block counter: %08x\n", ctr);

	uint8_t block[64];
	chacha20_core(block, key, nonce, ctr);

	puts("[DEBUG] serialized output block:");
	dump_bytes(block, 16, 0);
	dump_bytes(block, 16, 16);
	dump_bytes(block, 16, 32);
	dump_bytes(block, 16, 48);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// dump bytes in pretty-printed format
static void dump_bytes(uint8_t *bytes, int n, int offset) {
	for (int i = offset; i < offset + n; i++)
		printf("%02x ", bytes[i]);
	putchar('\n');
}
