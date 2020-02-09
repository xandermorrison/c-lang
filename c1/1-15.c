#include <stdio.h>

#define LOWER 0
#define UPPER 200
#define STEP 20

float converter(int fahr);

int main()
{
	int fahr;

	fahr = LOWER;

	printf("%4s%6s\n", "Fahr", "Cels");
	while (fahr <= 200) {
		printf("%4d%6.1f\n", fahr, converter(fahr));
		fahr += STEP;
	}
}

float converter(int fahr) {
	float cels;
	cels = (5.0 / 9.0) * (fahr - 32.0);
	return cels;
}
