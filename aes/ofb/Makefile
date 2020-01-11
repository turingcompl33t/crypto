# Makefile for AES OFB mode module. 

MAKE = make 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb

OBJS = ofb.o test.o 
LLIBS = ../cipher/cipher.a 

test: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# library, for module export 
lib: $(OBJS) 
	ar cr ofb.a $(OBJS)

../cipher/cipher.a:
	cd ../cipher/; $(MAKE) lib 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f ofb.a
	cd ../cipher; $(MAKE) clean

.PHONY: clean
	