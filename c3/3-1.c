#include <stdio.h>
#include <time.h>

int binsearch(int x, int v[], int n);

int main()
{
	clock_t begin = clock();

	int x = 20;
	int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	int n = 16; 

	int f;

	f = binsearch(x, v, n);

	printf("%d\n", f);

	clock_t end = clock();

	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("%f\n", time_spent);

	return 0;
}

int binsearch(int x, int v[], int n)
{
	int low, high, mid;

	low = 0;
	high = n - 1;

	mid = (low + high) / 2;

	while (low <= high && v[mid] != x)
	{
		if (x > v[mid])
		{
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
		mid = (low + high) / 2;
	}

	if (v[mid] == x)
	{
		return mid;
	}
	return -1;
}
