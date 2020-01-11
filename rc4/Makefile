# Makefile for rc4 module. 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11

test: test.o rc4.o
	$(CC) $(CFLAGS) $^ -o $@

vectors: vectors.o rc4.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f vectors 

.PHONY: clean
	