#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 1000
#define MAXLINE 40

int getch(void);
void ungetch(int);

int get_word(char *, int);

void replace_hex(char *);
void replace_oct(char *);

char *printnum(int i, int l);

int main()
{
	int len, charlen;
	int i, slen;
	char word[MAXWORD];

	int j, k, l;

	for (j = l = 0; j < MAXLINE; j++) {
		k = j % 10;
		if (k == 0)
			printf("%d", l++);
		else printf("%d", k);
	}
	printf("\n");

	charlen = 0;
	while ((len = get_word(word, MAXWORD)) > 0) {
		replace_hex(word);
		replace_oct(word);

		if (charlen + strlen(word) >= MAXLINE) {
			if (strlen(word) >= MAXLINE) {
				slen = strlen(word);
				for (i = 0; i < slen; i++) {
					if (charlen  >= MAXLINE - 1) {
						printf("\n");
						charlen = 0;
					}
					printf("%c", word[i]);
					charlen++;
				}
			}
			else {
				printf("\n");
				charlen = 0;
			}
		}
		else if (!(word[0] == ' ' && charlen == 0)) {
			printf("%s", word);
			charlen += strlen(word);
		}
	}
}

// START HEX FUNCTIONS

#define MAXVALS 100

int lowercheck(char);
int ishexc(int);
int convhexc(int);

int find_hex_start(char *);
int find_hex_end(char *, int);
void pop_hex_val(char *, int, int);
void remove_code(char *, int, int);

void replace_hex(char *w) 
{
	int start, end, i;
	i = 0;
	while ((start = find_hex_start(w)) > -1) {
		end = find_hex_end(w, start);
		pop_hex_val(w, start, end);
	}
}

int find_hex_start(char *w) 
{
	int i;
	for (i = 0; w[i] != '\0' && (i + 2) < strlen(w); i++) {
		if (w[i] == '0' && tolower(w[i+1]) == 'x' && ishexc(w[i+2])) {
			return i;
		}
	}
	return -1;
}

int find_hex_end(char *w, int s) 
{
	for (s += 2; ishexc(w[s]); s++) {
		;
	}
	return s;
}

void pop_hex_val(char *w, int s, int e)
{
	int v, i;
	char temp[MAXWORD];

	for (i = s + 2, v = 0; i < e; i++) {
		v = v * 16 + convhexc(w[i]);
	}

	remove_code(w, s, e);
	sprintf(temp, w, v);
	strcpy(w, temp);
}

void remove_code(char *w, int s, int e)
{
	w[s++] = '%';
	w[s++] = 'd';

	while (w[e] != '\0') {
		w[s++] = w[e++];
	}
	w[s] = '\0';
}

int convhexc(int i) {
	i = lowercheck(i);
	if (i >= '0' && i <= '9') {
		return i - '0';
	}
	else if (i >= 'a' && i <= 'f') {
		return i - 'a' + 10;
	}
	else {
		printf("error: not a hex char");
		return -1;
	}
}

int lowercheck(char i) {
	if (isupper(i)) {
		i = tolower(i);
		return i;
	}
	return i;
}

int ishexc(int i) {
	i = lowercheck(i);
	if (isdigit(i) || (i <= 'f' && i >= 'a')) {
		return 1;
	}
	else {
		return 0;
	}
}


// END HEX FUNCS
// OCT FUNCS

int isoctc(int i);

int find_oct_start(char *w) ;
int find_oct_end(char *w, int s) ;
void pop_oct_val(char *w, int s, int e);

void replace_oct(char *w) 
{
	int start, end, i;
	i = 0;
	while ((start = find_oct_start(w)) > -1) {
		end = find_oct_end(w, start);
		pop_oct_val(w, start, end);
	}
}

int find_oct_start(char *w) 
{
	int i;
	for (i = 0; w[i] != '\0' && (i + 1) < strlen(w); i++) {
		if (w[i] == '0' && isoctc(w[i + 1])) {
			return i;
		}
	}
	return -1;
}

int find_oct_end(char *w, int s) 
{
	for (s += 1; isoctc(w[s]); s++) {
		;
	}
	return s;
}

void pop_oct_val(char *w, int s, int e)
{
	int v, i;
	char temp[MAXWORD];

	for (i = s + 1, v = 0; i < e; i++) {
		v = v * 8 + (w[i] - '0');
	}

	remove_code(w, s, e);
	sprintf(temp, w, v);
	strcpy(w, temp);
}

int isoctc(int i) {
	if (i <= '7' && i >= '0') {
		return 1;
	}
	else {
		return 0;
	}
}

// END OCT FUNCS

int get_word(char *s, int max) {
	int c, i;
	i = 0;

	c = getch();

	if (c == EOF) {
		s[i] = '\0';
		return i;
	}

	s[i++] = c;
	s[i] = '\0';

	if (!isalnum(c)) {
		return i;
	}

	while (max-- > 0 && isalnum(c = getch())) {
		s[i++] = c;
	}
	ungetch(c);
	s[i] = '\0';

	return i;
}

#define BUFSIZE 100

int buf[BUFSIZE];
int bufp;

int getch(void)
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int i)
{
	if (bufp < BUFSIZE) {
		buf[bufp++] = i;
	}
	else {
		printf("error: no space for buffer unget");
	}
}
