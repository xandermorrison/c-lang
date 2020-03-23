#include <time.h>
#include <stdio.h>
#include <ctype.h>

clock_t start, end;
double cpu_time_used;

int myisupper(int);

int main()
{
	int i;

	start = clock();
	i = myisupper('A');
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("%f\n", cpu_time_used);

	start = clock();
	i = isupper('A');
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

	printf("%f\n", cpu_time_used);
}

int myisupper(int i)
{
	if (i >= 'A' && i <= 'Z') {
		return 1;
	}
	else {
		return 0;
	}
}
