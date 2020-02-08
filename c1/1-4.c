#include <stdio.h>

main() {
	float fahr, cels;
	int lower, upper, step;

	lower = 0;
	upper = 200;
	step = 20;

	printf("%5s\t%6s\n", "Cels", "Fahr");

	cels = lower;
	while (cels <= upper) {
		fahr = (cels * 9.0 / 5) + 32;
		printf("%5.0f\t%6.1f\n", cels, fahr);
		cels = cels + step;
	}
}

