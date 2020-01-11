// hash.c 
// Test program for Salsa20 hash function.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "salsa20.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static void print_vec(uint8_t *vec);

/* ----------------------------------------------------------------------------
	Test
*/

int main(void) {
	uint8_t vec1[] = {
		211,159, 13,115, 76, 55, 82,183, 3,117,222, 37,191,187,234,136,
		49,237,179, 48, 1,106,178,219,175,199,166, 48, 86, 16,179,207,
		31,240, 32, 63, 15, 83, 93,161,116,147, 48,113,238, 55,204, 36,
		79,201,235, 79, 3, 81,156, 47,203, 26,244,243, 88,118,104, 54
	};

	uint8_t vec2[] = {
		88,118,104, 54, 79,201,235, 79, 3, 81,156, 47,203, 26,244,243,
		191,187,234,136,211,159, 13,115, 76, 55, 82,183, 3,117,222, 37,
		86, 16,179,207, 49,237,179, 48, 1,106,178,219,175,199,166, 48,
		238, 55,204, 36, 31,240, 32, 63, 15, 83, 93,161,116,147, 48,113
	};

	uint8_t out1[64];
	uint8_t out2[64];

	salsa20_hash(out1, vec1);
	salsa20_hash(out2, vec2);

	// how did we do?
	puts("vector 1 in:");
	print_vec(vec1);
	puts("vector 1 salsa20 hash digest:");
	print_vec(out1);
	puts("vector 2 in:");
	print_vec(vec2);
	puts("vector 2 salsa20 hash digest:");
	print_vec(out2);

	return 0;
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// print byte vector in DJB's format
static void print_vec(uint8_t *vec) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 16; j++)
			printf("%4u", vec[(i*16)+j]);
		putchar('\n');
	}
}
