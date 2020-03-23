#include <stdio.h>

#define PAGELINES 5
#define MAXLINE 1000

int main(int argc, char *argv[])
{
	int pagecount, lineno;
	char *p, line[MAXLINE];

	if (argc > 1) {
		FILE *fp;
		p = line;

		while (--argc > 0) {
			fp = fopen(*++argv, "r");
			lineno = pagecount = 0;
			while (fgets(p, MAXLINE, fp) != NULL) {
				if (lineno == 0) {
					pagecount++;
					printf("---\n\nPage %d\n\n---\n", pagecount);
				}
				printf("%s", p);
				lineno++;
				if (lineno >= PAGELINES) {
					lineno = 0;
				}
			}
		}
	}
	else {
		printf("error: no files given to program\n");
		printf("usage: prog file1.txt file2.txt\n");
	}
}
