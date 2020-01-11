// test.c 
// Test program for Mersenne Twister PRNG.
//
// Usage:
//	test <n>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "mt.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		puts("ERROR: invalid arguments");
		puts("USAGE: test <n>");
		exit(1);
	}

	// yea, weak input validation, hack me
	int n = atoi(argv[1]);

	mt_t mt;
	uint32_t r;

	mt_seed(&mt, 5489); 

	for (int i = 0; i < n; i++) {
		r = mt_rand(&mt);
		printf("%08x\n", r); 
	}
	
	return 0;
}
