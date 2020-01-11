// key_schedule.h
// Key schedule generation. 

#ifndef __DES_KEY_SCHEDULE_H
#define __DES_KEY_SCHEDULE_H

/*
 * expand_key 
 * Expand key via DES key schedule algorithm.
 *
 * Arguments:
 *	key - cipher input key (8 bytes)
 *  key_schedule - buffer for entire key schedule 
 *		(16 rounds * 6 bytes = 96 bytes)
 */
void expand_key(uint8_t *key, uint8_t *key_schedule);

#endif // __DES_KEY_SCHEDULE_H
