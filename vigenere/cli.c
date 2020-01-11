// cli.c
// Command line interface to vigenere cipher.

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "vigenere.h"

/* ----------------------------------------------------------------------------
    Local Constants
*/

#define BUFSIZE 256

/* ----------------------------------------------------------------------------
    Local Prototypes
*/

size_t read_stdin(uint8_t *buf);
void write_stdout(uint8_t *buf, size_t buflen);

void hexdump(uint8_t *bytes, size_t len);

/* ----------------------------------------------------------------------------
    Main
*/

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR: invalid arguments\n");
        fprintf(stderr, "USAGE: vigenere <key>\n");
        exit(1);
    }

    // NOTE: this seriously lacks validation, sorry
    size_t klen = strlen(argv[1]);
    uint8_t key[klen];
    memcpy(key, argv[1], klen);

    uint8_t input[BUFSIZE]  = { 0 };
    uint8_t output[BUFSIZE] = { 0 };

    size_t mlen = read_stdin(input);

    vigenere(output, input, mlen, key, klen);

    write_stdout(output, mlen);

    return 0;
}

/* ----------------------------------------------------------------------------
    Local Functions
*/

// read bytes from stdin
size_t read_stdin(uint8_t *buf) {
    char c;
    size_t bidx = 0;
    while ((c = fgetc(stdin)) != EOF && !feof(stdin) && bidx < (BUFSIZE - 1))
        buf[bidx++] = c;

    buf[bidx] = '\0';

    return bidx;
}

// write bytes to stdout (ASCII)
void write_stdout(uint8_t *buf, size_t buflen) {
    for (size_t i = 0; i < buflen; i++)
        putchar(buf[i]);
}

// write bytes to stdout (hexadecimal)
void hexdump(uint8_t *bytes, size_t len) {
    for (size_t i = 0; i < len; i++) {
         printf("%02x ", bytes[i]);
     }
     putchar('\n');
 }
