# Makefile for cryptographic message authentication module. 

MAKE = make 

CC = gcc
CFLAGS = -Werror -pedantic -std=c11 -ggdb

OBJS = auth.o 
LLIBS = ../aes/cipher/cipher.a 

testecbc: $(OBJS) $(LLIBS) test_ecbc.o
	$(CC) $(CFLAGS) $^ -o test

breakrawcbc: $(OBJS) $(LLIBS) break_rawcbc.o
	$(CC) $(CFLAGS) $^ -o break

testcmac: $(OBJS) $(LLIBS) test_cmac.o
	$(CC) $(CFLAGS) $^ -o test

vercmac: $(OBJS) $(LLIBS) ver_cmac.o
	$(CC) $(CFLAGS) $^ -o ver

../aes/cipher/cipher.a:
	cd ../aes/cipher/; $(MAKE) lib 

clean:
	rm -f *.o 
	rm -f *.~
	rm -f test
	rm -f break 
	rm -f ver
	cd ../aes/cipher/; $(MAKE) clean

.PHONY: clean
