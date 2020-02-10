#include <stdio.h>
#define MAXLEN 1000

int get_line(char s[], int maxlen);
void reverses(char s[], int len);

int main()
{
	int len;
	char string[MAXLEN];

	while ((len = get_line(string, MAXLEN)) > 0)
	{
		reverses(string, len);
		printf("%s\n", string);
	}
}

int get_line(char s[], int maxlen)
{
	int c, i;

	for (i=0; i<maxlen-1 && (c = getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;

	s[i] = '\0';

	return i;
}

void reverses(char s[], int len)
{
	int i, j;
	char reversed[MAXLEN];

	--len;

	for (i = 0; len >= 0; --len)
	{
		reversed[i] = s[len];
		++i;
	}

	reversed[i] = '\0';

	for (j = 0; j <= i; ++j)
		s[j] = reversed[j];
}
