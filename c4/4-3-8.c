#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAXOP 100
#define NUMBER '0'
#define LETTER 'a'
#define ASSIGN '='

#define PRINT "print"
#define SWAP "swap"
#define CLEAR "clear"
#define DUP "duplicate"
#define SIN "sin"
#define EXP "exp"
#define POW "pow"

int check_strings(char s[], char t[]);
int getop(char []);
void push(double);
double pop(void);
double get_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

char var_names[46];
double var_values[46];

int var_index = 0;

int main()
{
	int type;
	int i, found;
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
				printf("\t%.8g\n", get_top());
				break;

			/* commands */
			case LETTER:
				if (strlen(s) == 1 && var_index > 0) {
					found = 0;
					for (i = 0; i < var_index; ++i) {
						if (s[0] == var_names[i]) {
							found = 1;
							push(var_values[i]);
						}
					}
					if (!found) {
						printf("error: unknown command %s\n", s);
					}
				}
				else if (check_strings(s, PRINT)) {
					printf("\tTOP: %.8g\n", get_top());
					break;
				}
				else if (check_strings(s, DUP)) {
					printf("\t%s\n", "DUPLICATING");
					duplicate_top();
				}
				else if (check_strings(s, SWAP)) {
					printf("\t%s\n", "SWAPPING");
					swap_top();
				}
				else if (check_strings(s, CLEAR)) {
					printf("\t%s\n", "CLEARING");
					clear_stack();
				}
				else if (check_strings(s, SIN)) {
					push(sin(pop()));
				}
				else if (check_strings(s, EXP)) {
					push(exp(pop()));
				}
				else if (check_strings(s, POW)) {
					op2 = pop();
					push(pow(pop(), op2));
				}
				else {
					printf("error: unknown command %s\n", s);
				}
				break;
			case ASSIGN:
				if (strlen(s) == 1) {
					found = 0;
					if (var_index > 0) {
						for (i = 0; i < var_index; ++i) {
							if (var_names[i] == s[0]) {
								found = 1;
								var_values[i] = get_top();
							}
						}
					}
					if (!found) {
						var_names[var_index] = s[0];
						var_values[var_index] = get_top();
						var_index++;
					}
				}
				else {
					printf("error: unknown command %s\n", s);
				}
				break;
					
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

int check_strings(char s[], char t[])
{
	int i, j;

	for (i = j = 0; s[i] == t[j] && s[i] != '\0'; ++i, ++j) {
		;
	}

	if (t[j] == '\0') {
		return 1;
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

double get_top(void)
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
void ungets(char []);

int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t') {
		;
	}

	s[1] = '\0';

	if (!isdigit(c) && c != '.' && c != '-') {
		if (isalpha(c)) {
			i = 0;
			while (isalpha(s[++i] = c = getch())) {
				;
			}
			s[i] = '\0';
			ungetch(c);
			return LETTER;
		}
		else if (c == ASSIGN) {
			c = getch();
			if (isalpha(c)) {
				s[0] = c;
				return ASSIGN;
			}
			else {
				ungetch(c);
				s[0] = '\0';
				return c;
			}
		}
		return c;
	}
	i = 0;
	if (c == '-') {
		c = getch();
		if (isdigit(c) || c == '.') {
			s[++i] = c;
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
		else {
			ungetch(c);
			return '-';
		}
		if (c == '.') {
			while (isdigit(s[++i] = c = getch())) {
				;
			}
		}
	}
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
		ungetch(c);
	}
	return NUMBER;
}

#define BUFSIZE 1

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

void ungets(char s[])
{
	int i;

	// ungetch string backwards because getch is stack

	for (i = strlen(s) - 1; i >= 0; --i) {
		ungetch(s[i]);
	}
}
