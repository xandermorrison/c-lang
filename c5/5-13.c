#include <stdio.h>
#include <ctype.h>
#define MAXCHARS 1000
#define MAXLINES 1000

int getlines(char *a, char *t[], int maxa, int maxt);
void ptail(char *l[], int n, int lineno);
int atoi(char *s);

int main(int argc, char *argv[])
{
	char text[MAXCHARS];
	char *lines[MAXLINES];

	int e;
	int tail = 10;
	
	if (argc > 1 && *argv[1] == '-') {
		tail = atoi(++argv[1]);
	}

	e = getlines(text, lines, MAXLINES, MAXCHARS);
	ptail(lines, tail, e);
}

int getlines(char *a, char *t[], int maxa, int maxt)
{
	int i, j;
	char c;

	for (i = 0, j = 0, t[j] = &a[i]; (c = getchar()) != EOF && 
			i < maxa - 1 && j < maxt - 1; i++) {
		a[i] = c;
		if (c == '\n') {
			a[++i] = '\0';
		}
		if (a[i - 1] == '\0') {
			t[++j] = a + i;
		}
	}
	a[i] = '\0';
	return j;
}

void ptail(char *l[], int n, int lineno)
{
	char **start, **end;

	end = l + lineno;
	start = l + lineno - n + 1;
	if (start < l) {
		start = l;
	}

	while (start <= end) {
		printf("%s", *start++);
	}
}

int atoi(char *s)
{
	int i = 0;
	while (isdigit(*s)) {
		i = i * 10 + (*s - '0');
		s++;
	}
	return i;
}
