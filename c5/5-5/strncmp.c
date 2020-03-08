#include <stdio.h>
#include <string.h>
#define MAXLEN 1000

int str_ncmp(char *cs, char *ct, int n);

int main()
{
	char s[MAXLEN] = "Where are you?";
	char t[MAXLEN] = "Wher?";

	int i;
	int n = 4;
	int o = 5;

	i = str_ncmp(s, t, n);
	printf("%d\n", i);

	i = str_ncmp(s, t, o);
	printf("%d\n", i);

	return 0;
}

int str_ncmp(char *cs, char *ct, int n)
{
	int i;

	while (n-- > 0 && (i=(*cs-*ct))==0 && *cs!='\0' && *ct!='\0') {
		cs++;
		ct++;
	}

	return i;
}
