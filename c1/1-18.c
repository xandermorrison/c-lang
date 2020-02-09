#include <stdio.h>
#define MAXLEN 1000

int get_line(char s[], int maxlength);
void strip_line(char s[], int len);

int main() 
{

	int len;
	char line[MAXLEN];

	while ((len = get_line(line, MAXLEN)) != 0) {
		strip_line(line, len);
		printf("%s\n", line);
	}
}

int get_line(char s[], int max)
{
	int c, i;

	for (i = 0; i<max-1 && (c = getchar())!=EOF && c!='\n'; ++i)
		s[i] = c;

	if (c == '\n') {
		s[i] = c;
		++i;
	}

	s[i] = '\0';

	return i;
}

void strip_line(char s[], int len)
{
	int i, last, rlast;

	last = rlast = -1;

	for (i = len - 1; i >= 0; --i)
		if (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			rlast = i;
	for (i = 0; i < len; ++i)
		if (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			last = i;

	++last;
	s[last] = '\0';

	if (rlast > -1)
		for (i = rlast; i < len; ++i)
			s[i - rlast] = s[i];

}
