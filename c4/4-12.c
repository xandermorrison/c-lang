#include <stdio.h>
#define MAXLEN 1000

void itoa(int i, char s[]);

int main()
{
	int i = 293343;
	char s[MAXLEN];

	itoa(i, s);

	printf("%s\n", s);

	return 0;
}

void itoa(int i, char s[])
{
	static int j = 0;

	if (i < 0) {
		s[j++] = '-';
		i = -i;
	}
	if (i / 10) {
		itoa(i / 10, s);
	}
	s[j++] = i % 10 + '0';
	s[j + 1] = '\0';
}
