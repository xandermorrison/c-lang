#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

char *itoa(int i, char *s);
void reverse(char *s, int end);

int main()
{
	int i = 39405;

	char s[MAXLEN];

	char *p;

	p = itoa(i, s);

	printf("%s\n", p);

	return 0;
}

char *itoa(int i, char *s)
{
	int sign = 1;
	char *p = s;

	if (i < 0) {
		sign = -1;
	}

	do {
		*s++ = (i % 10 * sign) + '0';
	} while ((i /= 10) > 0);

	if (sign < 0) {
		*s++ = '-';
	}

	*s = '\0';

	reverse(p, s - p - 1);

	return p;
}

void reverse(char *s, int end)
{
	int len, beg;

	len = strlen(s) - 1;
	beg = len - end;

	if (beg >= end) {
		return ;
	}

	char temp;
	temp = *(s + beg);
	*(s + beg) = *(s + end);
	*(s + end) = temp;

	reverse(s, end - 1);
}
