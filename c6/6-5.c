#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);

void undef(char *name);

int main()
{
	install("thatboy", "other");

	struct nlist *p = lookup("thatboy");

	if (p != NULL) {
		printf("%s\n", p->defn);
	}
	else {
		printf("Not found\n");
	}
	undef("thatboy");
	p = lookup("thatboy");

	if (p != NULL) {
		printf("%s\n", p->defn);
	}
	else {
		printf("Not found\n");
	}
}

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++) {
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
		if (strcmp(s, np->name) == 0) {
			return np;
		}
	}
	return NULL;
}

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL) {
			return NULL;
		}
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	}
	else {
		free((void *) np->defn);
	}
	if ((np->defn = strdup(defn)) == NULL) {
		return NULL;
	}
	return np;
}

void undef(char *name)
{
	struct nlist *np;
	
	int h = hash(name);

	for (np = hashtab[h]; np != NULL; np = np->next) {
		if (strcmp(name, np->name) == 0 && np == hashtab[h]) {
			hashtab[h] = np->next;
		}
		else if (strcmp(name, np->next->name) == 0) {
			np->next = np->next->next;
		}
	}
}
