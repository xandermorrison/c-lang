#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXLINE 1000
#define MAXWORD 1000

struct word {
	char *word;
	int lineno;
	int lines[MAXLINE];
	struct word *left;
	struct word *right;
};

int get_word(char *, int);
struct word *add_word(struct word *, char *, int);
void print_tree(struct word *);

int main()
{
	char c, word[MAXWORD];
	int lineno = 1;
	struct word *root;

	root = NULL;

	while ((c = get_word(word, MAXWORD)) != EOF) {
		if (c == '\n') {
			lineno++;
		}
		else if (isalpha(c) && strlen(word) > 3) {
			root = add_word(root, word, lineno);
		}
	}
	print_tree(root);
}

void print_tree(struct word *root)
{
	int i;
	if (root != NULL) {
		print_tree(root->left);
		printf("%10s:", root->word);
		for (i = 0; i < root->lineno; i++) {
			printf(" %d", root->lines[i]);
		}
		printf("\n");
		print_tree(root->right);
	}
}

struct word *w_alloc(void);
char *hldstr(char *s);

struct word *add_word(struct word *w, char *s, int l) 
{
	int cond;

	if (w == NULL) {
		w = w_alloc();
		w->word = hldstr(s);
		w->lineno = 0;
		w->lines[w->lineno++] = l;
		w->right = w->left = NULL;
	}
	else if ((cond = strcmp(s, w->word)) == 0) {
		if (w->lineno < MAXLINE) {
			w->lines[w->lineno++] = l;
		}
		else {
			printf("error: line array full");
		}
	}
	else if (cond < 0) {
		w->left = add_word(w->left, s, l);
	}
	else {
		w->right = add_word(w->right, s, l);
	}
	return w;
}

struct word *w_alloc(void)
{
	return (struct word *)malloc(sizeof(struct word));
}

char *hldstr(char *s)
{
	char *p = (char *)malloc(strlen(s) + 1);

	if (p != NULL) {
		strcpy(p, s);
	}
	return p;
}

int get_word(char *s, int max)
{
	char c;
	int getch(void);
	void ungetch(int);
	char *p = s;

	while ((c = getch()) == ' ' || c == '\t') {
		;
	}

	if (c != EOF) {
		*p++ = c;
	}

	if (!isalpha(c)) {
		*p = '\0';
		return c;
	}

	for (; --max > 0; p++) {
		if (!isalnum(*p = getch()) && *p != '\'') {
			ungetch(*p);
			break;
		}
	}
	*p = '\0';
	return s[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE) {
		printf("error: buffer full");
	}
	else {
		buf[bufp++] = c;
	}
}
