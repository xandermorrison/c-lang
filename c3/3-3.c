#include <stdio.h>
#define MAXLEN 1000

void expand(char s1[], char s2[]);

int main()
{
	char s1[MAXLEN] = "-This a-x is D-H1-9w-z-";

	char s2[MAXLEN];

	expand(s1, s2);

	printf("%s\n", s2);

	return 0;
}

void expand(char s1[], char s2[])
{
	int i, j, start, end;

	j = 0;

	for (i = 0; s1[i] != '\0'; ++i) {
		if (s1[i] == '-' && i != 0 && s1[i+1] != '\0') {
			start = s1[i - 1] + 1;
			end = s1[i + 1];

			while (start != end) {
				s2[j] = start;
				++start;
				++j;
			}
		}
		else {
			s2[j] = s1[i];
			++j;
		}
	}
}
