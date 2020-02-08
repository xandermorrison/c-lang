#include <stdio.h>

main() {
	int c;
	int b, t, n;

	b = t = n = 0;

	while ((c = getchar()) != EOF)
		if (c == ' ')
			++b;
		else if (c == '\t')
			++t;
		else if (c == '\n')
			++n;

	printf("\n", b);
	printf("%d spaces\n", b);
	printf("%d tabs\n", t);
	printf("%d newlines\n", n);
}
