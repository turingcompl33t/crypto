# Makefile for AES cipher module. 

CC = gcc
CFLAGS = -Wall -Werror -pedantic -std=c11 -ggdb
OBJS = mul.o util.o key_schedule.o sub_bytes.o shift_rows.o mix_cols.o 

# test program: no debugging output 
test: $(OBJS) aes test.o 
	$(CC) $(CFLAGS) $(OBJS) aes.o test.o -o test

# test program: debugging output 
debug: $(OBJS) daes test.o 
	$(CC) $(CFLAGS) $(OBJS) aes.o test.o -o test 

# library, for module export 
lib: $(OBJS) aes 
	ar cr cipher.a $(OBJS) aes.o

# aes recipe without debug flag
aes:
	$(CC) $(CFLAGS) -c -o aes.o aes.c 

# aes recipe with debug flag 
daes:
	$(CC) $(CFLAGS) -DDEBUG -c -o aes.o aes.c 

clean:
	rm -f *.o
	rm -f *.~
	rm -f test
	rm -f cipher.a 

.PHONY: clean
