// euclid.c 
// Playing with EA and EEA.

#include <stdio.h>
#include <stdlib.h>

unsigned int eea(unsigned int a, unsigned int b, int *s, int *t);

unsigned int ea_i(unsigned int a, unsigned int b);
unsigned int ea_r(unsigned int a, unsigned int b); 

int main(void) {
	int s;
	int t;

	unsigned int gcd = eea(973, 301, &s, &t); 
	printf("gcd = %u\n", gcd);
	printf("s   = %d\n", s);
	printf("t   = %d\n", t); 

	return 0;
}

// extended euclidean algorithm 
// compute gcd(a, b) = r = s*a + t*b
// return r, stuff s,t in params
unsigned int eea(unsigned int a, unsigned int b, int *s, int *t) {
 	// initial values for 'lookback' variables 
 	// x[i] denotes "value of x at timestep i":
 	int s_i2 = 1;  // s[i-2]
	int s_i1 = 0;  // s[i-1]
	int s_i;       // s[i]
	int t_i2 = 0;  // t[i-2]
	int t_i1 = 1;  // t[i-1]
	int t_i;       // t[i]
 
	int q;
	unsigned int tmp; 

	for (;;) {
		if (a % b == 0) {
			*s = s_i;
			*t = t_i; 
			return b;
		}

		tmp = b; 
		q   = a / b;
		b   = a % b;
		a   = tmp;

		s_i = s_i2 - q*s_i1;
		t_i = t_i2 - q*t_i1;

		s_i2 = s_i1;
		s_i1 = s_i;
		t_i2 = t_i1;
		t_i1 = t_i;
	}
}

// euclidean algorithm 
// compute gcd of a and b (iteratively)
unsigned int ea_i(unsigned int a, unsigned int b) {
	unsigned int tmp;
	for (;;) {
		if (a % b == 0)
			return b;
		tmp = b; 
		b   = a % b;
		a   = tmp;
	}
}

// euclidean algorithm 
// compute gcd of a and b (recursively)
unsigned int ea_r(unsigned int a, unsigned int b) {
	return (a % b == 0) ? b : ea_r(b, a % b);
}
