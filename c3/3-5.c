#include <stdio.h>
#define MAXLEN 1000

void itob(int n, char s[], int b);
void reverse(char s[]);

int main()
{
	int i = 38;

	// 2 is 100110
	// 8 is 46
	// 16 is 26
	
	char b[MAXLEN];
	char o[MAXLEN];
	char h[MAXLEN];

	itob(i, b, 2);
	itob(i, o, 8);
	itob(i, h, 16);

	printf("%s\n", b);
	printf("%s\n", o);
	printf("%s\n", h);

	return 0;
}

void itob(int n, char s[], int b)
{
	int i = 0;

	do {
		s[i++] = n % b + '0';
	} while ((n /= b) != 0);

	s[i] = '\0';

	reverse(s);
}

void reverse(char s[])
{
	int len, i, c;

	for (len = 0; s[len + 1] != '\0'; ++len) {
		;
	}

	for (i = 0; i < (len - i); ++i) {
		c = s[len - i];
		s[len - i] = s[i];
		s[i] = c;
	}
}
