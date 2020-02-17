#include <stdio.h>
#define MAX 1000

void escape(char s[], char t[]);
void rev_escape(char s[], char t[]);

int main()
{
	char s[MAX] = "This\nis\ta string\n.";
	char t[MAX];

	escape(s, t);

	printf("%s\n", s);
	printf("%s\n", t);

	rev_escape(t, s);

	printf("%s\n", t);
	printf("%s\n", s);

	return 0;
}

void escape(char s[], char t[])
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; ++i)
	{
		switch (s[i])
		{
			case ('\n'):
				t[j++] = '\\';
				t[j++] = 'n';
				break;
			case ('\t'):
				t[j++] = '\\';
				t[j++] = 't';
				break;
			default:
				t[j++] = s[i];
				break;
		}
	}
	t[j] = '\0';
}

void rev_escape(char s[], char t[])
{
	int i, j;

	for (i = j = 0; s[i] != '\0'; ++i)
	{
		switch (s[i])
		{
			case ('\\'):
				switch (s[++i])
				{
					case ('n'):
						t[j++] = '\n';
						break;
					case ('t'):
						t[j++] = '\t';
						break;
				}
				break;
			default:
				t[j++] = s[i];
				break;
		}
	}
	t[j] = '\0';
}
