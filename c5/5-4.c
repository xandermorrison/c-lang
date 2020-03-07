#include <stdio.h>

int str_end(char *s, char *t);

int main()
{
	char s[] = "Here we are";
	char t[] = " are";
	char r[] = "not";

	int result1 = str_end(s, t);
	int result2 = str_end(s, r);

	printf("%d\n", result1);
	printf("%d\n", result2);
}

int str_end(char *s, char *t)
{
	char *p;
	
	p = t;

	while (*s != '\0') {
		s++;
	}

	while (*p != '\0') {
		p++;
	}

	while (*s == *p) {
		if (t == p) {
			return 1;
		}
		--s;
		--p;
	}

	return 0;
}
