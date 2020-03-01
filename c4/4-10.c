#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define MAXLEN 1000
#define NUMBER '0'

int getop(char []);
int get_line(char [], int maxlen);
void push(double);
double pop(void);

char line[MAXLEN];
int l;

int main()
{
	int type;
	int len;
	double op2;
	char s[MAXOP];

	while ((len = get_line(line, MAXLEN)) > 0) {
		l = 0;
		while ((type = getop(s)) != '\0') {
			switch (type) {
				case NUMBER:
					push(atof(s));
					break;
				case '+':
					push(pop() + pop());
					break;
				case '*':
					push(pop() * pop());
					break;
				case '-':
					op2 = pop();
					push(pop() - op2);
					break;
				case '/':
					op2 = pop();
					if (op2 != 0.0) {
						push(pop() / op2);
					}
					else {
						printf("error: zero divisor\n");
					}
					break;
				case '\n':
					printf("\t%.8g\n", pop());
					break;
				default:
					printf("error: unknown command %s\n", s);
					break;
			}
		}
	}
	return 0;
}

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else {
		printf("error: stack full, can't push %g\n", f);
	}
}

double pop(void)
{
	if (sp > 0) {
		return val[--sp];
	}
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

int get_line(char s[], int m)
{
	int i;
	char c;

	for (i = 0; i < m-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i++] = c;
	}

	s[i] = '\0';
	return i;
}

#include <ctype.h>

int getop(char s[])
{
	int i;

	while ((s[0] = line[l++]) == ' ' || s[0] == '\t') {
		;
	}

	s[1] = '\0';

	if (!isdigit(s[0]) && s[0] != '.') {
		return s[0];
	}
	i = 1;
	if (isdigit(line[l])) {
		while (isdigit(line[l])) {
			s[i++] = line[l++];
		}
	}
	if (line[l] == '.') {
		s[++i] = line[l++];
		while (isdigit(line[l])) {
			s[++i] = line[l++];
		}
	}
	s[i] = '\0';
	return NUMBER;
}
