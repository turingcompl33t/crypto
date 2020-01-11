// ver_cmac.c 
// Test CMAC MAC computation and subsequent verification. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "auth.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void test_0(void);
static void test_1(void);

static void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	test_0();
	test_1();

	return 0;
}

// test zero-length message
static void test_0(void) {
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	uint8_t msg[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
	uint8_t tag[16];

	// generate the original tag
	auth_cmac_gen(tag, msg, 16, key);

	if (auth_cmac_ver(msg, 16, key, tag)) {
		puts("TEST 0: TAG VALID");
	} else {
		puts("TEST 0: TAG INVALID");
	}
}

static void test_1(void) {
	uint8_t key[] = { 0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c };

	uint8_t msg[] = { 0x6b, 0xc1, 0xbe, 0xe2, 0x2e, 0x40, 0x9f, 0x96, 0xe9, 0x3d, 0x7e, 0x11, 0x73, 0x93, 0x17, 0x2a };
	uint8_t tag[16];

	// generate the original tag
	auth_cmac_gen(tag, msg, 16, key);

	// modify the message: single bit change
	msg[0] ^= 0x01;

	if (auth_cmac_ver(msg, 16, key, tag)) {
		puts("TEST 1: TAG VALID");
	} else {
		puts("TEST 1: TAG INVALID");
	}
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
