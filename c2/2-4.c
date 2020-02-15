#include <stdio.h>

int squeeze(char s[], char b[]);

int main()
{
	int len;

	char s[] = "This is a test string";
	char b[] = "it";

	len = squeeze(s, b);

	printf("%s\n", s);

	return 0;
}

int squeeze(char s[], char b[])
{
	int i, j, k;
	int found;

	i = j = 0;

	for (; s[i] != '\0'; ++i)
	{
		found = 0;
		for (k = 0; b[k] != '\0'; ++k)
		{
			if (s[i] == b[k])
			{
				found = 1;
			}
		}
		if (!found)
		{
			s[j++] = s[i];
		}
	}
	s[j] = '\0';

	return j;
}
