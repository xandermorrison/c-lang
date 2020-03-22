#include <stdio.h>
#include <stdarg.h>

#define SIZE 100

void minprintf(char *fmt, ...);

int main()
{
	minprintf("%8d %.1f %s\n", 8, 2.3, "hello");
}

void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;

	int i;
	char temp[SIZE];

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}

		i = 0;
		while (*p != 'd' && *p != 'f' && *p != 's') {
			temp[i++] = *p++;
		}
		temp[i++] = *p;
		temp[i] = '\0';

		switch(temp[i - 1]) {
			case 'd':
				ival = va_arg(ap, int);
				printf(temp, ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf(temp, dval);
				break;
			case 's':
				sval = va_arg(ap, char *);
				printf(temp, sval);
				break;
			default:
				for (i = 0; temp[i] != '\0'; i++) {
					putchar(temp[i]);
				}
				break;
		}
	}
	va_end(ap);
}
