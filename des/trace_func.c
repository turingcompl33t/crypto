// trace_func.c
// Generate DES function traces. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "feistel.h"

int main(void) {
	uint8_t dst[4];
	uint8_t src[4]    = { 0x18, 0xCA, 0x18, 0xAD };
	uint8_t subkey[6] = { 0x19, 0x4C, 0xD0, 0x72, 0xDE, 0x8C };

	cipher_f(dst, src, subkey);

	return 0; 
}
