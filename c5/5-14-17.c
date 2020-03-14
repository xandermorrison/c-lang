#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXLINES 5000
#define MAXCHARS 5000

#define NUMERIC 'n'
#define REVERSE 'r'
#define FOLD 'f'
#define DIRORD 'd'

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char lines[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(void *lineptr[], int left, int right, int dirord,
		int (*comp)(void *, void *, int));
void reverse_ptr(void *lineptr[], int left, int right);

void encap(char *lineptr[], char *lines, int *caps, int lineno);
void decap(char *lineptr[], char *lines, int *caps, int lineno);

int str_cmp(char *, char *, int d);
int num_cmp(char *, char *, int d);

int main(int argc, char *argv[])
{
	int nlines;
	char lines[MAXCHARS] = "";
	int caps[MAXCHARS];

	int numeric, reverse, fold, dirord;
	numeric = reverse = fold = dirord = 0;
	char c;

	while (--argc > 0 && (*++argv)[0] == '-') {
		c = *++argv[0];
		switch (c) {
			case NUMERIC:
				numeric = 1;
				break;
			case REVERSE:
				reverse = 1;
				break;
			case FOLD:
				fold = 1;
				break;
			case DIRORD:
				dirord = 1;
				break;
		}
	}
		
	if ((nlines = readlines(lineptr, lines, MAXLINES)) >= 0) {

		if (fold) {
			decap(lineptr, lines, caps, nlines);
		}

		if (numeric) {
			qsort((void **)lineptr, 0, nlines - 1, dirord,
					(int (*)(void*, void*, int))(num_cmp));
		}
		else {
			qsort((void **)lineptr, 0, nlines - 1, dirord,
					(int (*)(void*, void*, int))(str_cmp));
		}

		if (fold) {
			encap(lineptr, lines, caps, nlines);
		}

		if (reverse) {
			reverse_ptr((void **)lineptr, 0, nlines - 1);
		}
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000
int get_line (char *, int);

int readlines(char *lineptr[], char l[], int maxlines)
{
	int len, nlines, sl;
	char *p, line[MAXLEN];

	nlines = 0;
	p = l;
	while ((len = get_line(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (sl = strlen(p)) >= MAXCHARS) {
			return -1;
		}
		else {
			p = p + sl + 1;
			line[len - 1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void decap(char *lineptr[], char *text, int *caps, int lineno)
{
	int i, r;
	int *ptr;
	char *lptr;

	for (i = 0; i < lineno; i++) {
		r = lineptr[i] - text;
		ptr = caps + r;
		lptr = lineptr[i];
		for (; *lptr != '\0'; lptr++, ptr++) {
			if (isupper(*lptr)) {
				*lptr = tolower(*lptr);
				*ptr = 1;
			}
			else {
				*ptr = 0;
			}
		}
	}
}

void encap(char *lineptr[], char *text, int *caps, int lineno)
{
	int i, r;
	int *ptr;
	char *lptr;

	for (i = 0; i < lineno; i++) {
		r = lineptr[i] - text;
		ptr = caps + r;
		lptr = lineptr[i];
		for (; *lptr != '\0'; lptr++, ptr++) {
			if (*ptr == 1) {
				*lptr = toupper(*lptr);
			}
		}
	}
}


void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0) {
		printf("%s\n", *lineptr++);
	}
}

int get_line(char s[], int lim)
{
	int c, i;

	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void qsort(void *v[], int left, int right, int d, int (*comp)(void*, void*, int))
{
	int i, last;
	void swap(void *v[], int i, int j);

	if (left >= right) {
		return ;
	}

	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((*comp)(v[i], v[left], d) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort(v, left, last-1, d, comp);
	qsort(v, last+1, right, d, comp);
}

double atof(char *s);

int str_cmp(char *s1, char *s2, int d)
{
	int i, j;

	for (i = 0, j = 0; s1[i] != '\0' && s2[j] != '\0'; i++, j++) {
		if (d) {
			while (!isdigit(s1[i]) && !isalpha(s1[i]) && !isspace(s1[i])) {
				i++;
			}
			while (!isdigit(s2[j]) && !isalpha(s2[j]) && !isspace(s2[j])) {
				j++;
			}
		}

		if (s1[i] != s2[j]) {
			return s1[i] - s2[j];
		}
	}

	if (s1[i] == '\0' && s1[i] == s2[j]) {
		return 0;
	}
	else {
		return s1[i] - s2[j];
	}
}

int num_cmp(char *s1, char *s2, int d)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1 < v2) {
		return -1;
	}
	else if (v1 > v2) {
		return 1;
	}
	else {
		return 0;
	}
}

double atof(char *s)
{
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++) {
		;
	}
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') {
		i++;
	}
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] == '.') {
		i++;
	}
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

void reverse_ptr(void *v[], int left, int right)
{
	void *temp;

	if (left >= right) {
		return ;
	}

	temp = v[left];
	v[left] = v[right];
	v[right] = temp;

	reverse_ptr(v, left+1, right-1);
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
