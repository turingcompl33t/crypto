// cli.c 
// Command line interface to chacha20 stream cipher. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "chacha20.h"

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
	uint8_t nonce[12];
	uint8_t block[64];
	uint8_t keystream[64];

	if (!parse_args(key, nonce, argc, argv))
		exit(1); 

	int nbytes;
	bool flag    = true;
	uint32_t ctr = 1;

	while (flag) {
		// generate next block of keystream
		chacha20_core(keystream, key, nonce, ctr++); 
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
		fprintf(stderr, "USAGE: chacha20 <32 byte key> <12 byte nonce>\n");
		return false;
	}

	if (strlen(argv[1]) != 32) {
		fprintf(stderr, "ERROR: key must be 32 bytes\n");
		return false;
	}

	if (strlen(argv[2]) != 12) {
		fprintf(stderr, "ERROR: nonce must be 12 bytes\n");
		return false;
	}

	for (int i = 0; i < 32; i++)
		key[i] = argv[1][i];
	for (int i = 0; i < 12; i++)
		nonce[i] = argv[2][i]; 

	return true;
}

// read a block (64 bytes) from stdin 
static int readblock(uint8_t *block) {
	char c;
	int bidx = 0;
	while (((c = getchar()) != EOF) && (bidx < 64)) {
		block[bidx++] = c; 
	}
	return bidx;
}
