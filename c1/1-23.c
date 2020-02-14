#include <stdio.h>

#define MAXLEN 1000

void getcode(char s[], int maxlen);
void clearcomments(char s[]);

int main()
{
	int c;
	char code[MAXLEN];

	getcode(code, MAXLEN);
	clearcomments(code);

	printf("%s", code);
}

void getcode(char s[], int maxlen)
{
	int c, i;

	for (i = 0; i < maxlen - 1 && (c = getchar()) != EOF; ++i)
	{
		s[i] = c;
	}

	s[i] = '\0';
}

void clearcomments(char s[])
{
	int i = 0, j, k;
	int inside_quotes = 0;

	while (s[i] != '\0')
	{
		if (s[i] == '/' && !inside_quotes)
		{
			j = i;
			if (s[i + 1] == '/')
			{
				while (s[j] != '\n')
				{
					++j;
				}
				++j;
				k = 0;
				while (s[j] != '\0')
				{
					s[i + k] = s[j];
					++k;
					++j;
				}
				s[i + k] = s[j];
			}
			else if (s[i + 1] == '*')
			{
				while (s[j] != '/' || s[j - 1] != '*')
				{
					++j;
				}
				++j;
				while (s[j] == '\n' || s[j] == ' ' || s[j] == '\t')
				{
					++j;
				}
				k = 0;
				while (s[j] != '\0')
				{
					s[i + k] = s[j];
					++k;
					++j;
				}
				s[i + k] = s[j];
			}
		}
		else if (s[i] == '"')
		{
			if (inside_quotes)
			{
				inside_quotes = 0;
			}
			else
			{
				inside_quotes = 1;
			}
			++i;
		}
		else
		{
			++i;
		}
	}
}
