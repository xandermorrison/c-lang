#include <stdio.h>

#define MAXLEN 1000 
#define TABSTOP 4

// returns len
int detab(char line[], int maxlen);

int main()
{
	int len;
	char string[MAXLEN];

	while ((len = detab(string, MAXLEN)) > 0)
	{
		printf("%s", string);
	}
}

int detab(char s[], int max)
{
	int c, i, r;

	i = 0;
	while (i<max && (c=getchar())!=EOF && c!='\n')
	{
		if (c == '\t') 
		{
			r = (i + 1) % TABSTOP;
			while (r <= TABSTOP) 
			{
				s[i] = ' ';
				++i;
				++r;
			}
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
