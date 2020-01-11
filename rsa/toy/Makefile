# Makefile for "toy" RSA stuff.

MAKE = make

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 

toy: toy_rsa.o toy_test.o 
	$(CC) $(CFLAGS) $^ -o $@

euclid: euclid.o 
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o 
	rm -f *.~
	rm -f toy 
	rm -f euclid

.PHONY: clean 
