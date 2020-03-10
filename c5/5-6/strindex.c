#include <stdio.h>

int strindex(char *s, char *t);

char pattern[] = "ould";

int main()
{
	int i;
	char s[] = "I could do it would";

	i = strindex(s, pattern);

	printf("%d\n", i);

	return 0;
}

int strindex(char *s, char *t)
{
	char *i, *j;

	char *p = s;

	for (; *s != '\0'; s++) {
		for (i = s, j = t; *j != '\0' && *j == *i; i++, j++) {
			;
		}
		if (j > t && *j == '\0') {
			return s - p;
		}
	}
	return -1;
}
