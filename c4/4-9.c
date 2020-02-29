#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

#define BUFSIZE 100

void ungetch(int c);
int getch(void);

signed int buf[BUFSIZE];
int bufp = 0;

int main()
{
	ungetch(EOF);
	
	printf("%d\n", buf[bufp - 1]);

	return 0;
}


int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp > BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
