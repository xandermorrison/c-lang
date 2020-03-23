#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int filecmp(char *, char *);

int main(int argc, char *argv[])
{
	if (argc != 3) {
		fprintf(stderr, "error\nusage: prog file1 file2\n");
	}

	int i = filecmp(argv[1], argv[2]);

	if (i == 0) {
		printf("No difference\n");
	}
	else {
		printf("Line: %d\n", i);
	}
}

int filecmp(char *s1, char *s2)
{
	int l;
	FILE *a, *b;
	char c[MAXLINE], d[MAXLINE];

	a = fopen(s1, "r");
	b = fopen(s2, "r");

	for (l = 1; fgets(c, MAXLINE, a) != NULL &&
			fgets(d, MAXLINE, b) != NULL; l++) {
		if (strcmp(c, d) != 0) {
			return l;
		}
	}
	return 0;
}
