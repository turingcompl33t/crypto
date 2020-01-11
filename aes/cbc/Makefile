# Makefile for AES CBC mode module. 

MAKE = make 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb

OBJS = cbc.o 
LLIBS = ../cipher/cipher.a 

test: $(OBJS) $(LLIBS) test.o
	$(CC) $(CFLAGS) $^ -o $@

# library, for module export 
lib: $(OBJS) 
	ar cr cbc.a $(OBJS)

../cipher/cipher.a:
	cd ../cipher/; $(MAKE) lib 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f cbc.a 
	cd ../cipher; $(MAKE) clean

.PHONY: clean
	