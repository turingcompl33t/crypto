// cli.c 
// Command line interface to salsa20 stream cipher. 
//
// Usage:
//	salsa <32 byte key> <8 byte nonce>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "salsa20.h"

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static bool parse_args(uint8_t *key, uint8_t *nonce, int argc, char *argv[]); 
static int readblock(uint8_t *block);

/* ----------------------------------------------------------------------------
	CLI Entry 
*/

int main(int argc, char *argv[]) {
	uint8_t key[32];
	uint8_t nonce[8];
	uint8_t block[64];
	uint8_t keystream[64];

	if (!parse_args(key, nonce, argc, argv))
		exit(1); 

	int nbytes;
	bool flag    = true;
	uint64_t ctr = 0;

	while (flag) {
		// generate next block of keystream
		salsa20_core(keystream, key, nonce, ctr++); 
		// read <= 64 byte block from stdin 
		if ((nbytes = readblock(block)) < 64)
			flag = false;
		// encrypt / decrypt via XOR with keystream
		for (int i = 0; i < nbytes; i++)
			block[i] ^= keystream[i];
		fwrite(block , 1, nbytes, stdout);
	}

	fflush(stdout); 
	return 0; 
}

/* ----------------------------------------------------------------------------
	Local Functions
*/

// parse command line arguments 
static bool parse_args(uint8_t *key, uint8_t *nonce, int argc, char *argv[]) {
	if (argc != 3) {
		fprintf(stderr, "ERROR: invalid arguments\n");
		fprintf(stderr, "USAGE: salsa20 <32 byte key> <8 byte nonce>\n");
		return false;
	}

	if (strlen(argv[1]) != 32) {
		fprintf(stderr, "ERROR: key must be 32 bytes\n");
		return false;
	}

	if (strlen(argv[2]) != 8) {
		fprintf(stderr, "ERROR: nonce must be 8 bytes\n");
		return false;
	}

	for (int i = 0; i < 32; i++)
		key[i] = argv[1][i];
	for (int i = 0; i < 8; i++)
		nonce[i] = argv[2][i]; 

	return true;
}

// read a block (64 bytes) from stdin 
static int readblock(uint8_t *block) {
	char c;
	int bidx = 0;
	while (((c = getchar()) != EOF) && (bidx < 64)) 
		block[bidx++] = c; 
	
	return bidx;
}
