# Makefile for AES CTR mode module. 

MAKE = make 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb

OBJS = ctr.o test.o 
LLIBS = ../cipher/cipher.a 

test: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ -o $@

# library, for module export 
lib: $(OBJS) 
	ar cr ctr.a $(OBJS)

../cipher/cipher.a:
	cd ../cipher/; $(MAKE) lib 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f ctr.a
	cd ../cipher; $(MAKE) clean

.PHONY: clean
	