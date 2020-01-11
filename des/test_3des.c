// test_3des.c
// Test program for 3DES encryption / decryption. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "des.h"
#include "util.h"

int main(void) {
    uint8_t key1[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t key2[] = {0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    uint8_t key3[] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF};
    
    uint8_t pt[]  = {0x12, 0x34, 0x56, 0xAB, 0xCD, 0x13, 0x25, 0x36};
    uint8_t ct[8];
    uint8_t nt[8];

    // do the thing
    des3_encrypt(ct, pt, key1, key2, key3);
    des3_decrypt(nt, ct, key1, key2, key3); 

    // how did we do?
    printf("%-20s", "KEY 1:");
    hexdump(key1, 8);
    printf("%-20s", "KEY 2:");
    hexdump(key2, 8);
    printf("%-20s", "KEY 3:");
    hexdump(key3, 8);

    printf("%-20s", "PLAINTEXT IN:");
    hexdump(pt, 8);
    printf("%-20s", "CIPHERTEXT:");
    hexdump(ct, 8);
    printf("%-20s", "PLAINTEXT OUT:");
    hexdump(nt, 8); 
    
    return 0;
}
