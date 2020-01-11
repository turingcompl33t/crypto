// break_rawcbc.c 
// Demonstration of raw CBC insecurity. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "auth.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void concat(uint8_t *dst, uint8_t *src, size_t size, size_t offset);
static void xor(uint8_t *r, uint8_t *a, uint8_t *b);
static void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	// Two Parties:
	// 	Alice -> legitimate user
	//	Bob   -> adversary

	// 1. Alice chooses (random) key under which she will MAC 
	uint8_t key[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};

	// 2. Bob selects arbitrary 1-block message m
	uint8_t msg1[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
	uint8_t tag1[16];

	// 3. Bob requests tag t for m; Alice computes raw CBC MAC on m
	auth_rawcbc(tag1, msg1, 16, key);

	// 4. Bob outputs t as MAC forgery for 2-block message m' = (m || t XOR m)
	printf("%-15s", "M' FORGERY: ");
	hexdump(tag1, 16);

	// is Bob's forgery valid?
	uint8_t tmp[16];
	uint8_t tag2[16];
	uint8_t msg2[32]; 
	xor(tmp, tag1, msg1);       // tmp <- t XOR m
	concat(msg2, msg1, 16, 0);  // m'[0..15]  <- m
	concat(msg2, tmp, 16, 16);  // m'[16..31] <- t XOR m

	auth_rawcbc(tag2, msg2, 32, key);

	printf("%-15s", "M' LEGITIMATE: ");
	hexdump(tag2, 16);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// dst[offset:offset+size] <- src[0:size]
static void concat(uint8_t *dst, uint8_t *src, size_t size, size_t offset) {
	for (size_t i = 0; i < size; i++)
		dst[i+offset] = src[i];
}

// block r <- block a ^ block b
static void xor(uint8_t *r, uint8_t *a, uint8_t *b) {
	for (int i = 0; i < 16; i++)
		r[i] = a[i] ^ b[i];
}

// print hexadecimal formatted bytes
static void hexdump(uint8_t *bytes, size_t len) {
	for (size_t i = 0; i < len; i++) 
		printf("%02x ", bytes[i]);
	putchar('\n');
}
