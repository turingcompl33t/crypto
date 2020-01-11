// crack.c
// Cryptopals Set 3, Challenge 22: Crack an MT19337 seed.

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "mt.h"

/* ----------------------------------------------------------------------------
	Global Variables 
*/

// raise the maximum value for more realistic scenarios
static const int WAIT_MAX = 10;  // maxmimum wait time
static const int WAIT_MIN =  4;  // minimum wait time 

/* ----------------------------------------------------------------------------
	Local Prototypes
*/

static uint32_t get_rand(void);

/* ----------------------------------------------------------------------------
	Main
*/

int main(void) {
	// using the builtin PRNG in a program that cracks our own PRNG; trippy
	srand(1);

	// get the random value, generated from unknown seed
	uint32_t r1 = get_rand();
	printf("got random value r = %u\n", r1); 

	mt_t mt;
	uint32_t r2; 
	uint32_t seed; 
	uint32_t now = (uint32_t) time(NULL);
	uint32_t past = now - 2*WAIT_MAX; 

	// iterate over the past seed (timestamp) values, 
	// comparing first output of PRNG with that computed from unknown seed
	for (seed = past; seed < now; seed++) {
		mt_seed(&mt, seed);
		r2 = mt_rand(&mt);
		if (r2 == r1) 
			break;
		
		// this is sloppy; MT module does not account for use case 
		// of many instances of the PRNG operating at the same time 
		free(mt.state); 
	}

	if (r2 == r1) {
		printf("got random value r = %u; cracked seed s = %u\n", r2, seed); 
	} else {
		puts("failed to crack seed");
	}

	return 0; 
}

/* ----------------------------------------------------------------------------
	Local Functions 
*/

// seed PRNG instance with unknown value, and return first result
static uint32_t get_rand(void) {
	mt_t mt;

	// wait a random number of seconds between WAIT_MIN and WAIT_MAX
	sleep(rand() % ((WAIT_MAX + 1 - WAIT_MIN) + WAIT_MIN));

	// seed instance of MT with current timestamp
	time_t now = time(NULL);
	mt_seed(&mt, (uint32_t) now);

	// inform us of the value we used, for verification
	printf("seeded PRNG instance with s = %u\n", (uint32_t) now); 

	// wait some more 
	sleep(rand() % ((WAIT_MAX + 1 - WAIT_MIN) + WAIT_MIN));

	// return first random output from MT
	return mt_rand(&mt);  
}
