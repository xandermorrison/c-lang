#include <stdio.h>

#define LEN 40
#define MAXLEN 1000

int fold(char s[], int maxlen);

int main()
{
	int t;
	int len;
	char s[MAXLEN];

	while ((len = fold(s, MAXLEN)) > 0)
	{
		for (t = 0; t < LEN; ++t)
		{
			printf("%c", '*');
		}
		printf("\n");
		printf("%s", s);
	}

	return 0;
}

int fold(char s[], int maxlen)
{
	int c, i, len;
	int j, wlen;
	char word[maxlen];

	i = 0;
	j = 0;
	len = 0;
	wlen = 0;

	while (i<maxlen-1 && (c=getchar())!=EOF && c!='\n')
	{
		if (c != ' ' && c != '\t')
		{
			word[wlen] = c;
			++wlen;
		}
		else
		{
			if (wlen > 0)
			{
				word[wlen] = '\0';

				if ((wlen + len) >= LEN)
				{
					s[i] = '\n';
					++i;
					len = 0;
				}
				for (j = 0; word[j] != '\0'; ++j)
				{
					if (len == LEN - 1)
					{
						s[i] = '\n';
						++i;
						len = 0;
					}
					s[i] = word[j];
					++i;
					++len;
				}
				wlen = 0;
			}
			if (len == LEN - 1)
			{
				s[i] = '\n';
				++i;
				len = 0;
			}
			s[i] = c;
			++i;
			++len;
		}
	}

	if (c == '\n')
	{
		if (wlen > 0)
		{
			word[wlen] = '\0';

			if ((wlen + len) >= LEN)
			{
				s[i] = '\n';
				++i;
				len = 0;
			}
			for (j = 0; word[j] != '\0'; ++j)
			{
				if (len == LEN - 1)
				{
					s[i] = '\n';
					++i;
					len = 0;
				}
				s[i] = word[j];
				++i;
				++len;
			}
		}
		s[i] = c;
		++i;
	}

	s[i] = '\0';
	return i;
}
