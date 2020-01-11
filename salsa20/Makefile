# Makefile for salsa20 related programs.

CC = gcc
CFLAGS = -Werror -pedantic -std=c11

# test without debugging
test: test.o salsa20
	$(CC) $(CFLAGS) test.o salsa20.o -o test

# test with debugging 
debug: test.o dsalsa20
	$(CC) $(CFLAGS) test.o salsa20.o -o debug

hash: hash.o salsa20
	$(CC) $(CFLAGS) hash.o salsa20.o -o hash

# command line application
cli: salsa20.o cli.o 
	$(CC) $(CFLAGS) $^ -o salsa20

# library, for export
lib: salsa20
	ar cr salsa.a salsa20.o

# without debug flag
salsa20:
	$(CC) $(CFLAGS) -c -o salsa20.o salsa20.c 

# with debug flag 
dsalsa20:
	$(CC) $(CFLAGS) -DDEBUG -c -o salsa20.o salsa20.c 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f debug 
	rm -f hash
	rm -f salsa.a 
	rm -f salsa20

.PHONY: clean

