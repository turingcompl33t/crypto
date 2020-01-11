# Makefile for DES implementation.

CC = gcc
CFLAGS = -Werror -pedantic -std=c11 -ggdb
OBJS = perm.o util.o key_schedule.o 

# DES standard run
testdes: $(OBJS) des feistel test_des.o 
	$(CC) $(CFLAGS) $(OBJS) des.o feistel.o test_des.o -o test 

# DES run with debugging output
debugdes: $(OBJS) ddes feistel debug_des.o
	$(CC) $(CFLAGS) $(OBJS) des.o feistel.o debug_des.o -o debug 

test3des: $(OBJS) des feistel test_3des.o 
	$(CC) $(CFLAGS) $(OBJS) des.o feistel.o test_3des.o -o test 

# trace cipher function
tracefunc: $(OBJS) des tfeistel trace_func.o 
	$(CC) $(CFLAGS) $(OBJS) des.o feistel.o trace_func.o -o tracefunc

# trace feistel net
tracefeistel: $(OBJS) des tfeistel trace_feistel.o 
	$(CC) $(CFLAGS) $(OBJS) des.o feistel.o trace_feistel.o -o tracefeistel

# without debugging 
des:
	$(CC) $(CFLAGS) -c -o des.o des.c

# with debugging 
ddes:
	$(CC) $(CFLAGS) -DDEBUG -c -o des.o des.c

# without tracing 
feistel:
	$(CC) $(CFLAGS) -c -o feistel.o feistel.c

# with tracing 
tfeistel:
	$(CC) $(CFLAGS) -DTRACE -c -o feistel.o feistel.c

clean:
	rm -f *.o 
	rm -f *.~
	rm -f test
	rm -f debug 
	rm -f tracefunc
	rm -f tracefeistel

.PHONY: clean
