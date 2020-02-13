#include <stdio.h>

#define MAXLEN 1000
#define TAB 4

int entab(char s[], int maxlen);
int unloader(int c, int i, char s[], char r);

int main()
{
	int len;
	char string[MAXLEN];

	while ((len = entab(string, MAXLEN)) > 0)
	{
		printf("%s", string);
	}
}

int entab(char s[], int maxlen)
{
	int c, i, spaces, tabs;

	i = spaces = 0;

	while (i<maxlen && (c=getchar())!=EOF && c!='\n')
	{
		if (c == ' ')
		{
			++spaces;
		}
		else
		{
			if (spaces)
			{
				tabs = spaces / TAB;
				spaces = spaces % TAB;
				i = unloader(tabs, i, s, '\t');
				i = unloader(spaces, i, s, ' ');
				spaces = 0;
			}
			s[i] = c;
			++i;
		}
	}

	if (c == '\n')
	{
		if (spaces)
		{
			tabs = spaces / TAB;
			spaces = spaces % TAB;
			i = unloader(tabs, i, s, '\t');
			i = unloader(spaces, i, s, ' ');
			spaces = 0;
		}
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}

int unloader(int c, int i, char s[], char r)
{
	while (c)
	{
		s[i] = r;
		++i;
		--c;
	}

	return i;
}
