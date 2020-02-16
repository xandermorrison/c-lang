#include <stdio.h>

char lower(char c);

int main()
{
	char c = 'T';

	c = lower(c);

	printf("%c\n", c);

	return 1;
}

char lower(char c)
{
	c = (c >= 'A' && c <= 'Z') ? (c - 'A' + 'a') : c;

	return c;
}
