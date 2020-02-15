#include <stdio.h>
#include <limits.h>
#include <float.h>

/* compile with 'gcc -H --fsyntax-only' to 
 * see where header files are */

int main() {
	printf("\nHeader Limits:\n");
	printf("CHAR_BIT%d\n", CHAR_BIT);
	printf("CHAR_MIN: %d\n", CHAR_MIN);
	printf("CHAR_MAX: %d\n", CHAR_MAX);
	printf("UCHAR_MAX: %i\n", UCHAR_MAX);
	printf("\n");
	printf("SHRT_MIN: %d\n", SHRT_MIN);
	printf("SHRT_MAX: %d\n", SHRT_MAX);
	printf("USHRT_MAX: %u\n", USHRT_MAX);
	printf("\n");
	printf("INT_MIN: %d\n", INT_MIN);
	printf("INT_MAX: %d\n", INT_MAX);
	printf("UINT_MAX: %u\n", UINT_MAX);
	printf("\n");
	printf("LONG_MIN: %ld\n", LONG_MIN);
	printf("LONG_MAX: %ld\n", LONG_MAX);
	printf("ULONG_MAX: %lu\n", ULONG_MAX);
	printf("\n");
	printf("FLT_MIN: %f\n", FLT_MIN);
	printf("FLT_MAX: %f\n", FLT_MAX);
	printf("\n");
	printf("DBL_MIN: %f\n", DBL_MIN);
	printf("DBL_MAX: %f\n", DBL_MAX);
	printf("\n\n");

	int cmax, cmin, ucmax;
	int smax, smin, usmax;
	long imax, imin, uimax;
	long lmin;
	unsigned long lmax, ulmax;

	cmax = (1 << ((sizeof(char) * 8) - 1)) - 1;
	cmin = -cmax - 1;
	ucmax = -cmin + cmax;
	smax = (1 << ((sizeof(short) * 8) - 1)) - 1;
	smin = -smax - 1;
	usmax = -smin + smax;
	imax = (1L << ((sizeof(int) * 8) - 1)) - 1;
	imin = -imax - 1;
	uimax = -imin + imax;
	lmax = (1UL << ((sizeof(long) * 8) - 1)) - 1;
	lmin = -lmax - 1;
	ulmax = -lmin + lmax;

	printf("Calculated Limits:\n");
	printf("CHAR_MIN: %dc\n", cmin);
	printf("CHAR_MAX: %d\n", cmax);
	printf("UCHAR_MAX: %d\n", ucmax);
	printf("\n");
	printf("SHRT_MIN: %d\n", smin);
	printf("SHRT_MAX: %d\n", smax);
	printf("USHRT_MAX: %d\n", usmax);
	printf("\n");
	printf("INT_MIN: %ld\n", imin);
	printf("INT_MAX: %ld\n", imax);
	printf("UINT_MAX: %ld\n", uimax);
	printf("\n");
	printf("LONG_MIN: %ld\n", lmin);
	printf("LONG_MAX: %lu\n", lmax);
	printf("ULONG_MAX: %lu\n", ulmax);
	printf("\n");

	return 0;
}
