#include <stdio.h>

main() {
	int c, s;

	while((c = getchar()) != EOF) {
		if (c == ' ' && s != 1) {
			s = 1;
			putchar(c);
		}
		else if (c != ' ') {
			s = 0;
			putchar(c);
		}
	}
}

