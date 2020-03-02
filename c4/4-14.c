#include <stdio.h>

#define swap(t, x, y) {t temp = x; x = y; y = temp;}

int main()
{
	int x = 1;
	int y = 2;

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	swap(int, x, y);

	printf("x = %d\n", x);
	printf("y = %d\n", y);

	return 0;
}
