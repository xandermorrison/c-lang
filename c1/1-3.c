#include <stdio.h>

main() {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	printf("%5s\t%6s\n", "Fahr", "Cels");

	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr - 32.0);
		printf("%5.0f\t%6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
