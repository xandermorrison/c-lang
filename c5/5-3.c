#include <stdio.h>
#define MAXLEN 100

void str_cat(char *s, char *t);

int main()
{
	char s[MAXLEN] = "Here we are and ";
	char t[MAXLEN] = "there we go!";

	str_cat(s, t);

	printf("%s\n", s);

	return 0;
}

void str_cat(char *s, char *t)
{
	while (*s != '\0') {
		s++;
	}

	while ((*s++ = *t++) != '\0') {
		;
	}
}
