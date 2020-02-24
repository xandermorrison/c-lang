#include <stdio.h>
#include <stdlib.h>

#define MAXOP 100
#define NUMBER '0'

int getop(char []);
void push(double);
double pop(void);
double print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

int main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
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
			case '%':
				op2 = pop();
				if (op2 != 0.0) {
					push((int)pop() % (int)op2);
				}
				else {
					printf("error: zero modulo\n");
				}
				break;
			case '\n':
				printf("\t%.8g\n", print_top());
				break;

			/* commands */
			case 'p':
				printf("\tTOP: %.8g\n", print_top());
				break;
			case 'd':
				printf("\t%s\n", "DUPLICATING");
				duplicate_top();
				break;
			case 's':
				printf("\t%s\n", "SWAPPING");
				swap_top();
				break;
			case 'c':
				printf("\t%s\n", "CLEARING");
				clear_stack();
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
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

double print_top(void)
{
	if (sp > 0) {
		return val[sp - 1];
	}
	else {
		printf("Stack empty\n");
		return 0.0;
	}
}

void duplicate_top(void)
{
	if (sp > 0) {
		val[sp] = val[sp - 1];
		++sp;
	}
	else {
		printf("error: stack empty\n");
	}
}

void swap_top(void)
{
	double temp;

	if (sp > 1) {
		temp = val[sp - 1];
		val[sp - 1] = val[sp - 2];
		val[sp - 2] = temp;
	}
	else {
		printf("error: stack must have at least 2 elements\n");
	}
}

void clear_stack(void)
{
	sp = 0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t') {
		;
	}

	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-') {
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
	if (c == '-') {
		c = getch();
		if (isdigit(c)) {
			s[++i] = c;
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
		else {
			ungetch(c);
			return '-';
		}
	}
	s[i] = '\0';
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
	if (bufp > BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}
