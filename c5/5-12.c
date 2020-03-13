#include <stdio.h>
#include <ctype.h>

#define TABS 100

#define TABSTOP 4

#define YES 1
#define NO 0

void settab(int argc, char *argv[], char *tab);
int atoi(char *a);
int tabpos(int pos, char *tab);

void entab(char *tab);
void detab(char *tab);

int main(int argc, char *argv[])
{
	char tab[TABS];
	settab(argc, argv, tab);
	entab(tab);
}

void entab(char *tab)
{
	int c, pos;
	int nb = 0;
	int nt = 0;

	for (pos = 0; (c = getchar()) != EOF; pos++) {
		if (c == ' ') {
			if (tab[pos] == NO) {
				++nb;
			}
			else {
				nb = 0;
				++nt;
			}
		}
		else {
			for (; nt > 0; nt--) {
				putchar('\t');
			}
			if (c == '\t') {
				nb = 0;
			}
			else {
				for (; nb > 0; nb--) {
					putchar(' ');
				}
			}
			putchar(c);
			if (c == '\n') {
				pos = 0;
			}
			else if (c == '\t') {
				while (tab[pos] != YES) {
					++pos;
				}
			}
		}
	}
}

void detab(char *tab)
{
	int c, pos = 0;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			do {
				putchar(' ');
			} while (tab[pos++] != YES);
		}
		else if (c == '\n') {
			putchar(c);
			pos = 0;
		}
		else {
			putchar(c);
			pos++;
		}
	}
}

void settab(int argc, char *argv[], char *tab)
{
	int i, pos, inc;

	if (argc <= 1) {
		for (i = 0; i < TABS; i++) {
			if (i % TABSTOP == 0) {
				tab[i] = YES;
			}
			else {
				tab[i] = NO;
			}
		}
	}
	else if (argc == 3 && *argv[1] == '-' && *argv[2] == '+') {
		pos = atoi(&(*++argv)[1]);
		inc = atoi(&(*++argv)[1]);
		for (i = 0; i < TABS; i++) {
			if (i != pos) {
				tab[i] = NO;
			}
			else {
				tab[i] = YES;
				pos += inc;
			}
		}
	}
	else {
		for (i = 1; i < TABS; i++) {
			tab[i] = NO;
		}
		while (--argc > 0) {
			pos = atoi(*++argv);
			if (pos > 0 && pos < TABS) {
				tab[pos] = YES;
			}
		}
	}
}

int atoi(char *a)
{
	int i;
	for (i = 0; isdigit(*a); a++) {
		i = i * 10 + (*a - '0');
	}
	return i;
}
