#include <stdio.h>
#include <string.h>

void reverse_in_place(char s[], int end);

int main()
{
	char s[] = "Where are you??";

	reverse_in_place(s, strlen(s) - 1);

	printf("%s\n", s);

	return 0;
}

void reverse_in_place(char s[], int end)
{
	int start = strlen(s) - 1 - end;

	if (start >= end) {
		return ;
	}

	char temp;
	temp = s[end];
	s[end] = s[start];
	s[start] = temp;
	reverse_in_place(s, end - 1);
}
