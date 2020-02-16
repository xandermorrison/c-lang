#include <stdio.h>

unsigned rightrot(unsigned x, int n);

int main()
{
	// x is 011010111;
	unsigned x = 0327;
	int rot = 3;

	x = rightrot(x, rot);

	printf("%d\n", x);
	printf("%d\n", 0732);

unsigned rightrot(unsigned x, int n)
{
	while (n-- > 0)
	{
		if (x & 1)
		{
			x = (x >> 1) | ~(~0u >> 1);
		}
		else
		{
			x >>= 1;
		}
	}
	return x;
}
