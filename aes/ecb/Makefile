# Makefile for AES ECB mode module. 

MAKE = make 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb

OBJS = ecb.o 
LLIBS = ../cipher/cipher.a 

test: $(OBJS) $(LLIBS) test.o 
	$(CC) $(CFLAGS) $^ -o $@

# library, for module export 
lib: $(OBJS) 
	ar cr ecb.a $(OBJS)

../cipher/cipher.a:
	cd ../cipher/; $(MAKE) lib 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	cd ../cipher; $(MAKE) clean

.PHONY: clean
