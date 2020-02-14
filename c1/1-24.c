#include <stdio.h>

#define MAXLEN 1000

void getcode(char s[], int maxlen);
void checksyntax(char s[]);

int main()
{
	int c;
	char code[MAXLEN];

	getcode(code, MAXLEN);
	checksyntax(code);
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

void checksyntax(char s[])
{
	int i, line_no;

	int inside_dquotes = 0;
	int squotes = 0;
	int squote_checked = 0;
	int inside_paren = 0;
	int inside_brace = 0;
	int inside_brack = 0;

	line_no = 1;

	for (i = 0; s[i] != '\0'; ++i)
	{
		if (s[i] == '"')
		{
			if (inside_dquotes)
			{
				inside_dquotes = 0;
			}
			else
			{
				inside_dquotes = 1;
			}

		}
		else if (s[i] == '\'')
		{
			if (s[i + 2] == '\'' || (s[i + 1] == '\\' && s[i + 3] == '\''))
			{
				squotes = 0;
				squote_checked = 1;
			}
			else if (squote_checked)
			{
				squote_checked = 0;
			}
			else
			{
				squotes = 1;
			}
		}
		else if (s[i] == '(')
		{
			++inside_paren;
		}
		else if (s[i] == '{')
		{
			++inside_brace;
		}
		else if (s[i] == '[')
		{
			++inside_brack;
		}
		else if (s[i] == ')')
		{
			--inside_paren;
		}
		else if (s[i] == '}')
		{
			--inside_brace;
		}
		else if (s[i] == ']')
		{
			--inside_brack;
		}
		else if (s[i] == '\n')
		{
			if (squotes)
			{
				printf("%s: %d\n", "Unmatched singled quote on line no", line_no);
				squotes = 0;
			}
			if (inside_dquotes)
			{
				printf("%s: %d\n", "Unmatched double quotes on line no", line_no);
				inside_dquotes = 0;
			}
			++line_no;
		}
	}

	if (inside_paren != 0)
	{
		printf("%s\n", "Unmatched parenthese in program");
	}
	if (inside_brace != 0)
	{
		printf("%s\n", "Unmatched braces in program");
	}
	if (inside_brack != 0)
	{
		printf("%s\n", "Unmatched brackets in program");
	}
}
