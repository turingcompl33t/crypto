// trace_feistel.c
// Generate DES feistel round traces. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "feistel.h"

int main(void) {
	uint8_t state[]  = { 0x14, 0xA7, 0xD6, 0x78, 0x18, 0xCA, 0x18, 0xAD };
	uint8_t subkey[] = { 0x19, 0x4C, 0xD0, 0x72, 0xDE, 0x8C };

	feistel(state, subkey);

	return 0; 
}
