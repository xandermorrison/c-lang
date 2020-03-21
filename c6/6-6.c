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

int main(int argc, char *argv[])
{
	if (argc == 4 & strcmp("#define", argv[1]) == 0) {
		install(argv[2], argv[3]);
		struct nlist *p = lookup(argv[2]);

		printf("%s\n", p->defn);
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
