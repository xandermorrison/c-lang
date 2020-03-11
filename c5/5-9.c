#include <stdio.h>

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
	int i, j, k;

	month_day(1988, 60, &j, &k);

	printf("%d %d\n", j, k);

	i = day_of_year(1988, 2, 29);

	printf("%d\n", i);
}

int day_of_year(int year, int month, int day)
{
	int i, leap;
	char (*p)[13];

	leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);
	
	p = daytab;

	p = leap ? p + 1 : p;

	for (i = 1; i < month; i++) {
		day += *(*p + i);
	}
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	char (*p)[13];

	leap = (year % 4 == 0) && (year % 100 != 0 || year % 400 == 0);

	p = daytab;

	p = leap ? p + 1 : p;

	for (i = 1; yearday > *(*p + i); i++) {
		yearday -= *(*p + i);
	}
	*pmonth = i;
	*pday = yearday;
}
