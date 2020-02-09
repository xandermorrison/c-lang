#include <stdio.h>

main()
{
	int c, i, j;
	int chars[26];

	for (i = 0; i < 26; ++i)
		chars[i] = 0;

	while ((c = getchar()) != EOF)
		if (c <= 'z' && c >= 'a') 
		{
			++chars[c - 'a'];
		}
		else if (c <= 'Z' && c >= 'A')
		{
			++chars[c - 'A'];
		}

	for (i = 0; i < 26; ++i) {
		printf("%c: ", i + 'a');
		for (j = 0; j < chars[i]; ++j)
			printf("#");
		printf("\n");
	}
}
