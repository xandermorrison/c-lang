#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

void itoa(int n, char s[], int p);
void reverse(char s[]);

int main()
{
	int i = 638;

	char s[MAXLEN];

	itoa(i, s, 40);

	printf("%s\n", s);

	return 0;
}


void itoa(int n, char s[], int p)
{
	int i, sign;

	if (n < 0) {
		sign = -1;
	}
	else {
		sign = 1;
	}

	i = 0;

	do {
		s[i++] = (n % 10 * sign) + '0';
	} while ((n /= 10) != 0);

	if (sign < 0)
		s[i++] = '-';

	while (i < p) {
		s[i++] = ' ';
	}

	s[i] = '\0';

	reverse(s);
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
