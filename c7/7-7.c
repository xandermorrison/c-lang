#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

//int get_line(char *line, int max);

int main(int argc, char *argv[])
{
	char *p, *pat, line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;
	size_t max = MAXLINE;
	FILE *fp;

	while (--argc > 0 && (*++argv)[0] == '-') {
		while ((c = *++argv[0])) {
			switch (c) {
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
		}
	}

	p = line;

	if (argc < 1) {
		printf("Usage: find -x -n pattern ");
		printf("*files(optional)\n");
	}
	pat = *argv;
	
	if (argc == 1) {
		while (getline(&p, &max, stdin) > 0) {
			lineno++;
			if ((strstr(line, pat) != NULL) != except) {
				if (number) {
					printf("%ld:", lineno);
				}
				printf("%s", line);
				found++;
			}
		}
	}
	else {
		while (--argc > 0) {
			fp = fopen(*++argv, "r");
			lineno = 0;
			printf("%s\n", *argv);
			while (fgets(p, MAXLINE, fp) != NULL) {
				lineno++;
				if ((strstr(p, pat) != NULL) != except) {
					if (number) {
						printf("%ld:", lineno);
					}
					printf("%s", line);
					found++;
				}
			}
			fclose(fp);
		}
	}
	return found;
}
