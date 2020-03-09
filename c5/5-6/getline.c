#include <stdio.h>

#define MAXLEN 1000

int get_line(char *s);

int main()
{
	int len;
	char s[MAXLEN];

	while ((len = get_line(s)) > 0) {
		printf("%s", s);
	}
	return 0;
}

int get_line(char *s)
{
	int i;

	for (i = 0; i < MAXLEN && (*s = getchar()) != '\n' && *s != EOF; ++i) {
		s++;
	}

	if (*s == '\n') {
		*s++ = '\n';
		++i;
	}

	*s = '\0';
	return i;
}
