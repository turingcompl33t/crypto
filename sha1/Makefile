# Makefile for SHA-1 test.

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb
OBJS = test.o 

# standard built
test: $(OBJS) sha1 
	$(CC) $(CFLAGS) $(OBJS) sha1.o -o test 

# debug build 
debug: $(OBJS) dsha1
	$(CC) $(CFLAGS) $(OBJS) sha1.o -o debug 

sha1:
	$(CC) $(CFLAGS) -c -o sha1.o sha1.c 

dsha1:
	$(CC) $(CFLAGS) -DDEBUG -c -o sha1.o sha1.c 

clean:
	rm -f *.o 
	rm -f *.~
	rm -f test 
	rm -f debug 

.PHONY: clean 
