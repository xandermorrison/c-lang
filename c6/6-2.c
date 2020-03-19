#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 100

enum status { NO, YES };

struct variable {
	char *var;
	struct variable *left;
	struct variable *right;
};

enum status in_string = NO;
enum status in_line_comment = NO;
enum status in_blk_comment = NO;

int get_word(char *s, int max);
int check_pattern(char *s1, char *s2);
struct variable *insert_variable(struct variable *, char *);

void print_tree(struct variable *root);

int main(int argc, char *argv[])
{
	int cond;
	char word[MAXWORD];
	char *p = "patter";

	struct variable *v = NULL;

	if (argc > 1 && strlen(argv[1]) == 6) {
		p = argv[1];
	}

	while (get_word(word, MAXWORD) != EOF) {
		/*printf("%s\n", word);
		printf("B: %d\n", in_blk_comment);
		printf("S: %d\n", in_string);
		printf("L: %d\n", in_line_comment);
		printf("\n");*/
		if (isalpha(word[0]) && check_pattern(p, word) &&
				!in_string && !in_line_comment && !in_blk_comment) {
			v = insert_variable(v, word);
		}
	}
	print_tree(v);
}

int check_pattern(char *s1, char *s2)
{
	int i;
	for (i = 0; s1[i] == s2[i] && i < 6; i++) {
		;
	}
	if (i == 6) {
		return 1;
	}
	else {
		return 0;
	}
}

void print_tree(struct variable *root)
{
	if (root != NULL) {
		print_tree(root->left);
		printf("%s\n", root->var);
		print_tree(root->right);
	}
}

char *hldwrd(char *w);
struct variable *v_alloc(void);

struct variable *insert_variable(struct variable *v, char *w)
{
	int cond;

	if (v == NULL) {
		v = v_alloc();
		v->var = hldwrd(w);
		v->left = v->right = NULL;
	}
	else if ((cond = strcmp(w, v->var)) < 0) {
		v->left = insert_variable(v->left, w);
	}
	else if (cond > 0) {
		v->right = insert_variable(v->right, w);
	}
	return v;

}

char *hldwrd(char *w)
{
	char *p;
	p = (char *)malloc(strlen(w) + 1);
	if (p != NULL) {
		strcpy(p, w);
	}
	return p;
}

struct variable *v_alloc(void)
{
	return (struct variable *)malloc(sizeof(struct variable));
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
		if (c == '"') {
			if (in_string == NO) {
				in_string = YES;
			}
			else {
				in_string = NO;
			}
		}
		else if (c == '/') {
			c = getch();
			if (c == '/') {
				in_line_comment = YES;
			}
			else if (c == '*') {
				in_blk_comment = YES;
			}
			else {
				ungetch(c);
			}
		}
		else if (c == '\n' && in_line_comment) {
			in_line_comment = NO;
		}
		else if (c == '*' && in_blk_comment) {
			c = getch();
			if (c == '/') {
				in_blk_comment = NO;
			}
			else {
				ungetch(c);
			}
		}
		*p = '\0';
		return c;
	}

	for (; --max > 0; p++) {
		if (!isalnum(*p = getch())) {
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
