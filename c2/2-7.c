#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main()
{
	// 111011010 0732
	// 110100010 0642

	unsigned x = 0732;

	int p = 6;
	int n = 4;

	x = invert(x, p, n);

	printf("%d\n", x);
	printf("check: %d\n", 0642);

	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	unsigned mask = ~(~0 << n) << (p + 1 - n);

	return x ^ mask;
}
