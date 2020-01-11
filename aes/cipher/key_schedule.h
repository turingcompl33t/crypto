// key_schedule.h
// Key schedule generation routines. 

#ifndef __AES_KEY_SCHEDULE_H
#define __AES_KEY_SCHEDULE_H

/* ----------------------------------------------------------------------------
	Global Functions - Round Key Addition 
*/

/*
 * add_round_key
 * Add round key to current state matrix. 
 */
void add_round_key(uint8_t *state, uint8_t *round_key); 

/* ----------------------------------------------------------------------------
	Global Functions - Key Expansion
*/

/*
 * expand_key
 * Expand cipher key according to key schedule algorithm. 
 *
 * This function implements the key schedule for all algorithm
 * key sizes: 128-bit, 192-bit, and 256-bit. 
 *
 * Arguments:
 *	key          - input cipher key
 *	key_schedule - buffer for resulting key schedule 
 *	nwords       - number of 32-bit words in input cipher key
 *	nrounds      - number of cipher rounds for algorithm key size
 */
void expand_key(uint8_t *key, uint8_t *key_schedule, size_t nwords, size_t nrounds);

#endif // __AES_KEY_SCHEDULE_H
