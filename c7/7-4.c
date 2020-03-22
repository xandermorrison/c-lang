#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 100

int get_line(char *, int);
void minscanf(char *fmt, ...);

int main()
{
	int i;
	double d;
	char s[MAXLINE];

	minscanf("%d %s %f", &i, s, &d);

	printf("%s\n", s);
	printf("%d\n", i);
	printf("%f\n", d);
}

void minscanf(char *fmt, ...) {
	va_list ap;
	char *p, *sval, *lptr, line[MAXLINE];
	int *ival, power, i;
	double *dval;

	get_line(line, MAXLINE);
	lptr = line;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (isspace(*p)) {
			continue;
		}

		while (isspace(*lptr)) {
			lptr++;
		}

		if (*p == '%') {
			switch(*++p) {
				case 'd':
					ival = va_arg(ap, int *);
					*ival = 0;
					if (isdigit(*lptr)) {
						while (isdigit(*lptr)) {
							*ival = *ival*10+(*lptr++-'0');
						}
					}
					else {
						printf("format error\n");
						return ;
					}
					break;
				case 'f':
					dval = va_arg(ap, double *);
					*dval = 0.0;
					power = 1.0;
					if (isdigit(*lptr) || *lptr == '.') {
						while (isdigit(*lptr)) {
							*dval = *dval*10+(*lptr++-'0');
						}
						if (*lptr == '.') {
							lptr++;
						}
						while (isdigit(*lptr)) {
							*dval = *dval*10+(*lptr++-'0');
							power *= 10.0;
						}
						*dval /= power;
					}
					else {
						printf("Tformat error\n");
						return ;
					}
					break;
				case 's':
					sval = va_arg(ap, char *);
					i = 0;
					while (isalpha(*lptr) && i < MAXLINE-1) {
						sval[i++] = *lptr++;
					}
					sval[i] = '\0';
					if (i >= MAXLINE-1) {
						printf("str storage cap reached\n");
					}
					break;
				default:
					break;
			}
		}
		else {
			if (*lptr++ != *p) {
				printf("format error\n");
				return ;
			}
		}
	}
	va_end(ap);
}

int get_line(char *s, int max)
{
	int c, i;
	i = 0;
	while ((c = getchar()) != '\n' && max-- > 1) {
		s[i++] = c;
	}

	s[i] = '\0';
	return i;
}


