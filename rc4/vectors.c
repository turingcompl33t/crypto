// vectors.c
// Validate RC4 keystream with official specification
//	RFC 2669: "Test Vectors for the Stream Cipher RC4"

#include <stdio.h>
#include <stdlib.h>

#include "rc4.h"

// length of the keystream, in bytes
// maximum offset 4096 + 16 = 4112
#define STREAM_LEN 4112

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void gen_vec(uint8_t *key, size_t keylen); 
static void print_stream_at_offset(uint8_t *stream, size_t offset);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	// 40 bit key
	size_t keylen_40 = 5;
	uint8_t key_40[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

	// 56 bit key
	size_t keylen_56 = 7;
	uint8_t key_56[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07 };

	// 64 bit key
	size_t keylen_64 = 8;
	uint8_t key_64[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

	// 128 bit key
	size_t keylen_128 = 16;
	uint8_t key_128[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10 };

	// 192 bit key
	size_t keylen_192 = 24;
	uint8_t key_192[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10,
						  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18 
						};

	// 256 bit key
	size_t keylen_256 = 32;
	uint8_t key_256[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 
						  0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20 
						};

	// generate test vectors
	gen_vec(key_40,  keylen_40); 
	gen_vec(key_56,  keylen_56); 
	gen_vec(key_64,  keylen_64); 
	gen_vec(key_128, keylen_128); 
	gen_vec(key_192, keylen_192); 
	gen_vec(key_256, keylen_256); 

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// generate the RFC-formatted test vector for specified key parameters
static void gen_vec(uint8_t *key, size_t keylen) {
	// display key parameters 
	printf("Key len: %lu bits\n", keylen * 8);
	printf("Key    : 0x");
	for (size_t i = 0; i < keylen; i++)
		printf("%02x", key[i]);
	putchar('\n');

	// generate the keystream
	uint8_t stream[STREAM_LEN];
	rc4_stream(stream, STREAM_LEN, key, keylen);

	// display keystream values at various offsets
	print_stream_at_offset(stream, 0); 
	print_stream_at_offset(stream, 16);
	print_stream_at_offset(stream, 240);
	print_stream_at_offset(stream, 256);
	print_stream_at_offset(stream, 496);
	print_stream_at_offset(stream, 512);
	print_stream_at_offset(stream, 752);
	print_stream_at_offset(stream, 768);
	print_stream_at_offset(stream, 1008);
	print_stream_at_offset(stream, 1024);
	print_stream_at_offset(stream, 1520);
	print_stream_at_offset(stream, 1536);
	print_stream_at_offset(stream, 2032);
	print_stream_at_offset(stream, 2048);
	print_stream_at_offset(stream, 3056);
	print_stream_at_offset(stream, 3072);
	print_stream_at_offset(stream, 4080);
	print_stream_at_offset(stream, 4096);
	putchar('\n'); 
}

// print 16 bytes of keystream beginning from specified offset
static void print_stream_at_offset(uint8_t *stream, size_t offset) {
	printf("DEC %4zd HEX %4zx: ", offset, offset);
	for (size_t i = offset; i < (offset + 16); i++) 
		printf("%02x ", stream[i]);
	putchar('\n');
}
