#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
#define FLAGNUM 5

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	int flags[FLAGNUM];
	int fd;
} FILE;

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

int _READ = 1;
int _WRITE = 1;
int _UNBUF = 1;
int _EOF = 1;
int _ERR = 1;

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0 },
	{ 0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1},
	{ 0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2 }
};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)

#define getc(p) (--(p)->cnt >= 0 \
		? (unsigned char) *(p)->ptr++ : _fillbuf(p))
#define putc(x,p) (--(p)->cnt >= 0 \
		? *(p)->ptr++ = (x) : _flushbuf((x),p))

#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)

#include <fcntl.h>
#include <unistd.h>
#define PERMS 0666

FILE *f_open(char *name, char *mode)
{
	int fd, i;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		return NULL;
	}
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
		if ((fp->flags[0] & _READ) == 0 && (fp->flags[1] & _WRITE) == 0) {
			break;
		}
	}
	if (fp >= _iob + OPEN_MAX) {
		return NULL;
	}

	if (*mode == 'w') {
		fd = creat(name, PERMS);
	}
	else if (*mode == 'a') {
		if ((fd = open(name, O_WRONLY, 0)) == -1) {
			fd = creat(name, PERMS);
		}
		lseek(fd, 0L, 2);
	}
	else {
		fd = open(name, O_RDONLY, 0);
	}
	if (fd == -1) {
		return NULL;
	}
	fp->fd = fd;
	fp->cnt = 0;
	fp->base = NULL;
	for (i = 0; i < FLAGNUM; i++) {
		fp->flags[i] = 0;
	}
	if (*mode == 'r') {
		fp->flags[0] = 1;
	}
	else if (*mode == 'w') {
		fp->flags[1] = 1;
	}
	return fp;
}

#include <stdlib.h>

int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flags[0] & _READ) == 1 && 
				((fp->flags[3] & _EOF) == 1 || (fp->flags[4] & _ERR) == 1)) {
		return EOF;
	}
	bufsize = (fp->flags[2] & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL) {
			return EOF;
		}
	}
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->flags[3] = 1;
		}
		else {
			fp->flags[4] = 1;
		}
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

#include <time.h>

int main()
{
	FILE *fp;
	int c;

	clock_t start, end;
	double cpu_time_used;

	start = clock();
	fp = f_open("test.txt", "r");
	while ((c = getc(fp)) != EOF) {
		;
	}
	end = clock();
	cpu_time_used = ((double)start/end) / CLOCKS_PER_SEC;
}
