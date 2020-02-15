#include <stdio.h>

/* returns first location of character from s2 in s1*/
int any(char s1[], char s2[]);

int main()
{
	int loc;

	char s[] = "This is the test string";
	char c[] = "clt";
	
	loc = any(s, c);

	printf("%d\n", loc);

	return 0;
}

int any(char s1[], char s2[])
{
	int i, j;
	int loc;

	loc = -1;

	for (i = 0; s1[i] != '\0'; ++i)
	{
		for (j = 0; s2[j] != '\0'; ++j)
		{
			if (s1[i] == s2[j] && loc == -1)
			{
				loc = i;
			}
		}
	}
	return loc;
}
