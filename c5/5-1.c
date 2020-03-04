#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);
int get_int(int*);

int main()
{
	int i;
	int result;

	result = get_int(&i);
	
	if (result)
		printf("%d\n", i);
}

int get_int(int *pn)
{
	int c, sign;

	while(isspace(c = getchar())) {
		;
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}

	sign = (c == '-') ? -1 : 1;

	if (c == '+' || c == '-') {
		c = getch();
	}
	if (!isdigit(c)) {
		ungetch(c);
		return 0;
	}
	for (*pn = 0; isdigit(c); c = getch()) {
		*pn = 10 * *pn + (c - '0');
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFLEN 100

int buf[BUFLEN];
int bufp;

int getch(void)
{
	return (bufp > 0) ? buf[bufp--] : getchar();
}

void ungetch(int c)
{
	if (bufp > BUFLEN - 1) {
		printf("Buffer limit exceeded");
	}
	else {
		buf[bufp++] = c;
	}
}
