#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
	int c, (*convert)(int);

	while (*argv[0] == '.' || *argv[0] == '/') {
		argv[0]++;
	}

	if (isupper(*argv[0])) {
		convert = toupper;
	}
	else {
		convert = tolower;
	}

	while ((c = getchar()) != EOF) {
		putchar((*convert)(c));
	}
}
