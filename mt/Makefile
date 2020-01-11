# Makefile for MT19937. 

CC = gcc
CFLAGS = -Werror -pedantic -std=c11 -ggdb 

test: test.o mt
	$(CC) $(CFLAGS) test.o mt.o -o test

debug: test.o dmt 
	$(CC) $(CFLAGS) test.o mt.o -o test

clone: clone.o mt 
	$(CC) $(CFLAGS) clone.o mt.o -o clone

crack: crack.o mt 
	$(CC) $(CFLAGS) crack.o mt.o -o crack

cipher: cipher.o mt 
	$(CC) $(CFLAGS) cipher.o mt.o -o cipher

# without debugging 
mt:
	$(CC) $(CFLAGS) -c -o mt.o mt.c 

# with debugging
dmt:
	$(CC) $(CFLAGS) -DDEBUG -c -o mt.o mt.c 

temper: temper.o
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o 
	rm -f *.~ 
	rm -f test 
	rm -f clone
	rm -f crack
	rm -f temper 
	rm -f cipher

.PHONY: clean
