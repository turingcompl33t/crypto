# Makefile for vigenere cipher.

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11

cli: cli.o vigenere.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f *.~
	rm -f cli
	rm -f *.txt

.PHONY: clean
