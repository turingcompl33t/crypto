// temper.c
// Messing around with inverting generator tempering function. 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint32_t untemper_r(uint32_t r, int shift, uint32_t mask);
uint32_t untemper_l(uint32_t r, int shift, uint32_t mask); 

int main(void) {
	uint32_t y0 = 0x41424344;
	printf("y0 = %x\n", y0);

	uint32_t y1 = y0 ^ ((y0 << 4) & 0x11FFAAFF);
	printf("y1 = %x\n", y1);

	uint32_t y2 = untemper_l(y1, 4, 0x11FFAAFF); 
	printf("y2 = %x\n", y2);

	return 0;
}

uint32_t untemper_r(uint32_t r, int shift, uint32_t mask) {
	int i = 1;
	uint32_t submask = (0xFFFFFFFF << (32 - shift));

	for (int recovered = shift; recovered < 32; recovered += shift) 
		r ^= ((r >> shift) & mask) & (submask >> shift*i++);
	
	return r; 
}

uint32_t untemper_l(uint32_t r, int shift, uint32_t mask) {
	int i = 1;
	uint32_t submask = ~(0xFFFFFFFF << shift);

	for (int recovered = shift; recovered < 32; recovered += shift) 
		r ^= ((r << shift) & mask) & (submask << shift*i++);
	
	return r; 
}
