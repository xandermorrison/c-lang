#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main()
{
	char s[] = "0xf3B1";

	int i = htoi(s);

	printf("%d\n", i);

	return 0;
}

int htoi(char s[])
{
	int i = 0;
	int c;
	int total = 0;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
	{
		i = 2;
	}

	for (; s[i] != '\0'; ++i)
	{
		if (isdigit(s[i]))
		{
			total = 16 * total + (s[i] - '0');
		}
		else
		{
			c = tolower(s[i]);
			total = 16 * total + (c - 'a' + 10);
		}
	}

	return total;
}
