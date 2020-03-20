#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXWORD 1000

struct word {
	char *word;
	int occurs;
	struct word *left;
	struct word *right;
};

int get_word(char *, int);
struct word *add_word(struct word *, char *);
struct word *sort_words(struct word *);
void print_tree(struct word *);

int main()
{
	char c, word[MAXWORD];
	struct word *root;

	root = NULL;
	while ((c = get_word(word, MAXWORD)) != EOF) {
		if (isalpha(c)) {
			root = add_word(root, word);
		}
	}
	struct word *s = sort_words(root);
	print_tree(s);
}

/* print binary tree so that words with
 * most occurrences are listed first */

void print_tree(struct word *root)
{
	if (root != NULL) {
		print_tree(root->right);
		printf("%8d : %s\n", root->occurs, root->word);
		print_tree(root->left);
	}
}

// sort binary tree functions

struct word *get_node(struct word *);
struct word *insert_node(struct word *, struct word *);
struct word *remove_node(struct word *, char *);

struct word *sort_words(struct word *root)
{
	struct word *p, *r;

	r = NULL;
	while (root != NULL) {
		p = get_node(root);
		r = insert_node(r, p);
		root = remove_node(root, p->word);
	}

	return r;
}

struct word *insert_node(struct word *r, struct word *p)
{
	int cond;

	if (r == NULL) {
		r = p;
	}
	else if (r->occurs == p->occurs) {
		if ((cond = strcmp(p->word, r->word)) < 0) {
			r->right = insert_node(r->right, p);
		}
		else {
			r->left = insert_node(r->left, p);
		}
	}
	else if (r->occurs > p->occurs) {
		r->left = insert_node(r->left, p);
	}
	else {
		r->right = insert_node(r->right, p);
	}
	return r;
}

struct word *get_node(struct word *word)
{
	if (word->left != NULL) {
		word = get_node(word->left);
	}
	else if (word->right != NULL) {
		word = get_node(word->right);
	}
	return word;
}

struct word *remove_node(struct word *root, char *w)
{
	int cond, child_cond;

	if ((cond = strcmp(w, root->word)) == 0) {
		root = NULL;
	}
	else if (cond < 0) {
		if (strcmp(w, root->left->word) == 0) {
			root->left = NULL;
		}
		else {
			root->left = remove_node(root->left, w);
		}
	}
	else {
		if (strcmp(w, root->right->word) == 0) {
			root->right = NULL;
		}
		else {
			root->right = remove_node(root->right, w);
		}
	}
	return root;
}

// allocating space for string and word struct

struct word *w_alloc(void);
char *hldstr(char *s);

struct word *add_word(struct word *w, char *s) 
{
	int cond;

	if (w == NULL) {
		w = w_alloc();
		w->word = hldstr(s);
		w->occurs = 1;
		w->right = w->left = NULL;
	}
	else if ((cond = strcmp(s, w->word)) == 0) {
		w->occurs++;
	}
	else if (cond < 0) {
		w->left = add_word(w->left, s);
	}
	else {
		w->right = add_word(w->right, s);
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

// get word functions

int get_word(char *s, int max)
{
	char c;
	int getch(void);
	void ungetch(int);
	char *p = s;

	while (isspace(c = getch())) {
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
