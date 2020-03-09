#include <stdio.h>
#include <ctype.h>

int atoi(char *s);

int main()
{
	char s[] = "9203";

	int i = atoi(s);

	printf("%d\n", i);

	return 0;
}

int atoi(char *s)
{
	int i, n;

	n = 0;

	while (isdigit(*s)) {
		n = n * 10 + (*s - '0');
		s++;
	}

	return n;
}
