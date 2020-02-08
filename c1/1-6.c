#include <stdio.h>

main() {
	int c;
	char value = (c = getchar()) != EOF;

	while (value) {
		printf("%c\t%d\n", c, value);
		value = (c = getchar()) != EOF;
	}

	printf("%c\t%d\n", c, value);
}
