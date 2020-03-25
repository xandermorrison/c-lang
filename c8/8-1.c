#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

int std_cat(int argc, char *argv[]);
void std_filecopy(FILE *ifp, FILE *ofp);
int unix_cat(int argc, char *argv[]);
void cat_filecopy(int ifp, int ofp);

int main(int argc, char *argv[])
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	unix_cat(argc, argv);
	end = clock();

	cpu_time_used = ((double)(end-start)) / CLOCKS_PER_SEC;

	printf("TIME: %lf\n", cpu_time_used);
}

int std_cat(int argc, char *argv[])
{
	FILE *fp;
	void std_filecopy(FILE *, FILE *);
	char *prog = argv[0];

	if (argc == 1) {
		std_filecopy(stdin, stdout);
	}
	else {
		while (--argc > 0) {
			if ((fp = fopen(*++argv, "r")) == NULL) {
				printf("%%\n");
				fprintf(stderr, "%s: can't open %s\n",
						prog, *argv);
				return 1;
			}
			else {
				std_filecopy(fp, stdout);
				fclose(fp);
			}
		}
	}
	if (ferror(stdout)) {
		fprintf(stderr, "%s: error writing stdout\n", prog);
		return 2;
	}
	return 0;
}

void std_filecopy(FILE *ifp, FILE *ofp)
{
	int c;

	while ((c = getc(ifp)) != EOF) {
		putc(c, ofp);
	}
}

int unix_cat(int argc, char *argv[])
{
	int fp;
	void cat_filecopy(int, int);
	char *prog = argv[0], msg[100];

	if (argc == 1) {
		cat_filecopy(0, 1);
	}
	else {
		while (--argc > 0) {
			if ((fp = open(*++argv, O_RDONLY, 0)) == -1) {
				printf("%%\n");
				sprintf(msg, "%s: can't open %s\n",
						prog, *argv);
				write(2, msg, strlen(msg));
				return 1;
			}
			else {
				cat_filecopy(fp, 1);
				close(fp);
			}
		}
	}
	return 0;
}

void cat_filecopy(int ifp, int ofp)
{
	int n;
	char buf[BUFSIZ];

	while ((n = read(ifp, buf, BUFSIZ)) > 0) {
		write(ofp, buf, n);
	}
}
