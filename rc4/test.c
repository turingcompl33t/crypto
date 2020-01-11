// test.c

#include <stdio.h>
#include <stdlib.h>

#include "rc4.h"

int main(void) {
	size_t keylen = 5;
	uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

	uint8_t buf[4096];

	rc4_stream(buf, 4096, key, keylen);

	for (size_t i = 0; i < 4096; i++) {
		printf("%02x\n", buf[i]);
	}

	return 0;
}
