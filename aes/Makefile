# Makefile for AES library.

MAKE = make 

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb

LIB = aes.a
OBJS = 

# build the library
$(LIB): $(OBJS)
	ar cr $@ $^

clean:
	cd cipher; $(MAKE) clean
	cd ecb; $(MAKE) clean
	cd cbc; $(MAKE) clean 

.PHONY: clean
