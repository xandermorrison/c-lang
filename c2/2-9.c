#include <stdio.h>

int bitcount(unsigned x);

int main()
{
	// x = 011001111; 6 1 bits
	unsigned x = 0317;
	
	int b = bitcount(x);	

	printf("%d\n", b);

	return 0;
}

int bitcount(unsigned x)
{
	int b = 0;

	while (x > 0)
	{
		x &= (x - 1);
		++b;
	}
	return b;
}
