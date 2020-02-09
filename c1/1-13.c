#include <stdio.h>

#define IN 1
#define OUT 0

main()
{
	int c, i, j, len;
	int lengths[20];

	len = 0;
	for (i = 0; i < 20; ++i)
		lengths[i] = 0;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (len > 0 && len < 21) {
				++lengths[len - 1];
				len = 0;
			}
		}
		else
			++len;
	}

	for (i = 0; i < 20; ++i) {
		printf("%d: ", i + 1);
		for (j = 0; j < lengths[i]; ++j)
			printf("#");
		printf("\n");
	}
}
