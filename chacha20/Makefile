# Makefile for chacha20 and related primitives.

CC = gcc
CFLAGS = -Werror -pedantic -std=c11

test_core: dchacha20 test_core.o
	$(CC) $(CFLAGS) chacha20.o test_core.o -o $@

test_cipher: dchacha20 test_cipher.o
	$(CC) $(CFLAGS) chacha20.o test_cipher.o -o $@

# library, for export
lib: chacha20
	ar cr chacha20.a chacha20.o

# command line application
cli: chacha20 cli.o 
	$(CC) $(CFLAGS) chacha20.o cli.o -o chacha20

# without debug output
chacha20:
	$(CC) $(CFLAGS) -c -o chacha20.o chacha20.c 

# with debug output
dchacha20:
	$(CC) $(CFLAGS) -DDEBUG -c -o chacha20.o chacha20.c 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test_core
	rm -f test_cipher
	rm -f chacha20
	rm -f chacha20.a 

.PHONY: clean
