#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

int get_line(char line[], int max);
int strrindex(char s[], char t[]);

char pattern[] = "world";

int main()
{
	char line[MAXLEN];
	int i;
	int found = 0;

	while (get_line(line, MAXLEN) > 0) {
		if ((i = strrindex(line, pattern)) >= 0) {
			printf("%s: %d\n", line, i);
			++found;
		}
	}

	return found;
}

int get_line(char line[], int max)
{
	int c, i;

	i = 0;

	while (max > 0 && (c = getchar()) != EOF && c != '\n') {
		line[i++] = c;
	}

	if (c == '\n') {
		line[i++] = c;
	}

	line[i] = '\0';

	return i;
}

int strrindex(char s[], char t[])
{
	int i, j, k;

	for (i = (strlen(s) - 1); i >= 0; --i) {
		for (j = i, k = 0; s[j] == t[k] && t[k] != '\0'; ++j, ++k) {
			;
		}
		if (t[k] == '\0' && k > 0) {
			return i;
		}
	}

	return -1;
}
