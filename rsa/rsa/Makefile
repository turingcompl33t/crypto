# Makefile for RSA implementation.

MAKE = make

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 

LLIBS = ../../bignum/bignum.a

test: $(LLIBS) rsa.o test.o 
	$(CC) $(CFLAGS) $^ -o $@

../../bignum/bignum.a:
	cd ../../bignum; $(MAKE) lib

clean:
	rm -f *.o 
	rm -f *.~
	rm -f test 
	cd ../../bignum; $(MAKE) clean

.PHONY: clean 
