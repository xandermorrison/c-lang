#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include "direct.h"
#undef DIRSIZ
#define DIRSIZ 14

void fsize(char *);

int main(int argc, char *argv[])
{
	if (argc == 1) {
		fsize(".");
	}
	else {
		while (--argc > 0) {
			fsize(*++argv);
		}
	}
}

//int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
	struct stat stbuf;

	if (stat(name, &stbuf) == -1) {
		fprintf(stderr, "fsize: can't access %s\n", name);
		return ;
	}
	if ((stbuf.st_mode & S_IFMT) == S_IFDIR) {
		dirwalk(name, fsize);
	}
	printf("%8lld: %.3o: %s\n", stbuf.st_size,
		   stbuf.st_mode % 040000, name);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
	char name[MAX_PATH];
	Dirent *dp;
	DIRX *dfd;

	if ((dfd = open_dir(dir)) == NULL) {
		fprintf(stderr, "dirwalk: can't open %s\n", dir);
		return ;
	}
	while ((dp = read_dir(dfd)) != NULL) {
		if (strcmp(dp->name, ".") == 0 ||
				strcmp(dp->name, "..") == 0) {
			continue;
		}
		if (strlen(dir) + strlen(dp->name) + 2 >
				sizeof(name)) {
			fprintf(stderr, "dirwalk: name %s/%s too long\n",
					dir, dp->name);
		}
		else {
			sprintf(name, "%s/%s", dir, dp->name);
			(*fcn)(name);
		}
	}
	close_dir(dfd);
}

//int fstat(int fd, struct stat *);
#include <stdlib.h>

DIRX *open_dir(char *dirname)
{
	int fd;
	struct stat stbuf;
	DIRX *dp;

	if ((fd = open(dirname, O_RDONLY, 0)) == -1 ||
			fstat(fd, &stbuf) == -1 ||
			(stbuf.st_mode & S_IFMT) != S_IFDIR ||
			(dp = (DIRX *) malloc(sizeof(DIRX))) == NULL) {
		return NULL;
	}
	dp->fd = fd;
	return dp;
}

void close_dir(DIRX *dp)
{
	if (dp) {
		close(dp->fd);
		free(dp);
	}
}

Dirent *read_dir(DIRX *dp)
{
	struct direct dirbuf;
	static Dirent d;

	while (read(dp->fd, (char *) &dirbuf, sizeof(dirbuf))
			== sizeof(dirbuf)) {
		if (dirbuf.d_ino == 0) {
			continue;
		}
		d.ino = dirbuf.d_ino;
		strncpy(d.name, dirbuf.d_name, DIRSIZ);
		d.name[DIRSIZ - 1] = '\0';
		return &d;
	}
	return NULL;
}
