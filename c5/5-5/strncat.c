#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

char *str_ncat(char *s, char *ct, int n);

int main()
{
	char s[MAXLEN] = "Where are you ";
	char t[MAXLEN] = "Now that I need you?";

	char *p;

	int n = 6;

	p = str_ncat(s, t, n);

	printf("%s\n", p);

	return 0;
}

char *str_ncat(char *s, char *ct, int n)
{
	char *i;
	char *j;

	i = s;
	j = ct;

	while (*i != '\0') {
		++i;
	}

	while ((*i++ = *j++) != '\0' && (j - ct) < n) {
		;
	}

	*i = '\0';

	return s;
}
