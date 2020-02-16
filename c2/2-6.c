#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() 
{
	unsigned result;
	// x is 110010100
	unsigned x = 0624;
	// y is 010111011
	unsigned y = 0273;

	// result should be 110011100 or 0634

	int p = 5;
	int n = 3;

	result = setbits(x, p, n, y);	

	printf("%d\n", result);
	printf("check: %d\n", 0634);
	
	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	unsigned y_mask = ~(~0 << n);

	unsigned x_mask = ~(~(~0 << n) << (p + 1 - n));

	x = x & x_mask;

	unsigned target = y & y_mask;

	target <<= (p + 1 - n);

	x = x | target;

	return x;
}
