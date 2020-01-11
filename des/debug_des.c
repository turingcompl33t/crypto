// debug_des.c
// Debugging program for DES encryption / decryption. 
//  (just like the test enc./dec. program, without extra output)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "des.h"
#include "util.h"

int main(void) {
    uint8_t key[] = {0xAA, 0xBB, 0x09, 0x18, 0x27, 0x36, 0xCC, 0xDD};
    uint8_t pt[]  = {0x12, 0x34, 0x56, 0xAB, 0xCD, 0x13, 0x25, 0x36};
    uint8_t ct[8];
    uint8_t nt[8];

    // do the thing
    des_encrypt(ct, pt, key);
    des_decrypt(nt, ct, key); 
    
    return 0;
}
