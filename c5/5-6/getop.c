#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXLEN 1000

int getop(char *s);

int main()
{
	int type;
	char s[MAXLEN];

	while ((type = getop(s)) != EOF) {
		printf("%d\n", type);
	}
	return 0;
}

int getch(void);
void ungetch(int);

int getop(char *s)
{
	int i, c;

	while ((*s = c = getchar()) == ' ' || c == '\t') {
		;
	}
	*(s + 1) = '\0';
	
	if (!isdigit(c) && c != '.') {
		return c;
	}
	if (isdigit(c)) {
		while (isdigit(*(++s) = c = getchar())) {
			;
		}
	}
	if (c == '.') {
		while (isdigit(*(++s) = c = getchar())) {
			;
		}
	}
	*s = '\0';
	if (c != EOF) {
		ungetch(c);
	}
	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
