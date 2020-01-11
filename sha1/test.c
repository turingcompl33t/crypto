// test.c 
// Test program for SHA-1 digest computation.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "sha1.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

void test_single_block (void);
void test_multi_block  (void);

void print_message (uint8_t *message, size_t len); 
void print_digest  (uint32_t *digest);

/* ----------------------------------------------------------------------------
	Main 
*/

int main(void) {
	test_single_block();
	test_multi_block();

	return 0; 
}

/* ----------------------------------------------------------------------------
	Test Cases
*/

// test a single-block message
void test_single_block(void) {
	// input message "abc"
	// 3 bytes = 24 bits 
	uint8_t  msg[] = {0x61, 0x62, 0x63};
	uint32_t digest[5];

	// compute the hash 
	sha1(digest, msg, 3); 

	// how did we do? 
	puts("input:");
	print_message(msg, 3);
	puts("digest:");
	print_digest(digest);
}

// test a multi-block message
void test_multi_block(void) {
	// "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"
	// 56 bytes = 448 bits 
	uint8_t msg[56] = {
		0x61, 0x62, 0x63, 0x64, 0x62, 0x63, 0x64, 0x65, 0x63, 0x64, 0x65, 0x66, 0x64, 0x65, 0x66, 0x67,
		0x65, 0x66, 0x67, 0x68, 0x66, 0x67, 0x68, 0x69, 0x67, 0x68, 0x69, 0x6a, 0x68, 0x69, 0x6a, 0x6b, 
		0x69, 0x6a, 0x6b, 0x6c, 0x6a, 0x6b, 0x6c, 0x6d, 0x6b, 0x6c, 0x6d, 0x6e, 0x6c, 0x6d, 0x6e, 0x6f,
		0x6d, 0x6e, 0x6f, 0x70, 0x6e, 0x6f, 0x70, 0x71
	}; 
	uint32_t digest[5];

	sha1(digest, msg, 56);

	puts("input:");
	print_message(msg, 56);
	puts("digest:");
	print_digest(digest);
}

/* ----------------------------------------------------------------------------
	Misc. Helpers
*/

// print raw message bytes as ASCII characters
void print_message(uint8_t *message, size_t len) {
	printf("  ");
	for (size_t i = 0; i < len; i++) {
		printf("%c", message[i]); 
	}
	putchar('\n');
}

// print hash digest as 5 32-bit words
void print_digest(uint32_t *digest) {
	printf("  ");
	for (size_t i = 0; i < 5; i++) {
		printf("%08x ", digest[i]);
	}
	putchar('\n'); 
}
