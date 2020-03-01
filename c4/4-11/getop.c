#include <stdio.h>
#include <ctype.h>
#include "calc.h"

int getop(char s[])
{
	int i, c;

	static int unget = EOF;

	if (unget == EOF || unget == ' '  || unget == '\t') {
		while ((s[0] = c = getchar()) == ' ' || c == '\t') {
			;
		}
	}
	else {
		s[0] = c = unget;
	}

	s[1] = '\0';

	if (!isdigit(c) && c != '.') {
		return c;
	}
	i = 0;
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch())) {
			;
		}
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch())) {
			;
		}
	}
	s[i] = '\0';
	if (c != EOF) {
		unget = c;
	}
	return NUMBER;
}
