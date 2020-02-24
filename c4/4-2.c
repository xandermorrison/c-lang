#include <stdio.h>
#include <ctype.h>

double atof(char s[]);
double scinot(double val, char s[], int i);

int main()
{
	char s[] = "123.45E-6";
	double check = 0.00012345;

	double t = atof(s);

	printf("%.8f\n", t);
	printf("%.8f\n", check);

	return 0;
}

double atof(char s[])
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); ++i) {
		;
	}

	sign = (s[i] == '-') ? -1 : 1;

	if (sign == '+' || sign == '-') {
		i++;
	}

	for (val = 0.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
	}

	if (s[i] == '.') {
		++i;
	}

	for (power = 1.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}

	val = sign * val / power;

	if (tolower(s[i++]) == 'e') {
		val = scinot(val, s, i);
	}

	return val;
}

double scinot(double val, char s[], int i)
{
	int sign, sci;

	sign = (s[i] == '-') ? -1 : 1;

	if (s[i] == '+' || s[i] == '-') {
		++i;
	}

	for (sci = 0; isdigit(s[i]); ++i) {
		sci = 10 * sci + (s[i] - '0');
	}

	if (sign < 0) {
		for (; sci > 0; --sci) {
			val /= 10;
		}
	}
	else {
		for (; sci > 0; --sci) {
			val *= 10;
		}
	}

	return val;
}
