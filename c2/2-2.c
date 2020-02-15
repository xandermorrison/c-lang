#include <stdio.h>

#define MAXLEN 1000

int get_line(char s[], int maxlen);

int main()
{
	int l;
	char s[MAXLEN];

	while ((l = get_line(s, MAXLEN)) > 0)
	{
		printf("%s", s);
	}
	return 0;
}

int get_line(char s[], int lim)
{
	int c, i;

	i = 0;

	while (i < lim - 1)
	{
		c = getchar();
		if (c == '\n')
		{
			lim = 0;
		}
		else if (c == EOF)
		{
			lim = 0;
		}
		else
		{
			s[i] = c;
			++i;
		}
	}

	if (c == '\n')
	{
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}
