#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

char *str_ncpy(char *s, char *t, int n);

int main()
{
	char s[MAXLEN] = "Where are you";
	char t[MAXLEN] = "Now that I need you";

	int n = 6;

	char *p;

	p = str_ncpy(s, t, n);
	printf("%s\n", p);

	return 0;
}

char *str_ncpy(char *s, char *ct, int n)
{
	char *i;
	char *j;
	i = s;
	j = ct;

	while ((*i++ = *j++) != '\0' && (j - ct) < n) {
		;
	}

	if ((j - ct) < n) {
		*j++ = '\0';
	}

	return s;
}
