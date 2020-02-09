#include <stdio.h>
#define MAXLEN 1000

int get_line(char s[], int maxlength);

int main()
{
	int len;
	char string[MAXLEN];

	while ((len = get_line(string, MAXLEN)) > 0)
		if (len > 80)
			printf("%s", string);

	return 0;
}

int get_line(char s[], int maxlength)
{
	int c, i, len;

	for (i = 0; i<maxlength-1 && (c=getchar()) != EOF && c!='\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}
