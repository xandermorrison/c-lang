#define NULL 0
#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20

typedef struct _iobuf {
	int cnt;
	char *ptr;
	char *base;
	int flag;
	int fd;
} FILE;

enum _flags {
	_READ = 01,
	_WRITE = 02,
	_UNBUF = 04,
	_EOF = 010,
	_ERR = 020
};

FILE _iob[OPEN_MAX] = {
	{ 0, (char *) 0, (char *) 0, _READ, 0 },
	{ 0, (char *) 0, (char *) 0, _WRITE, 1},
	{ 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

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
	int fd;
	FILE *fp;

	if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
		return NULL;
	}
	for (fp = _iob; fp < _iob + OPEN_MAX; fp++) {
		if ((fp->flag & (_READ | _WRITE)) == 0) {
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
	fp->flag = (*mode == 'r') ? _READ : _WRITE;
	return fp;
}

#include <stdlib.h>

int _fillbuf(FILE *fp)
{
	int bufsize;

	if ((fp->flag&(_READ|_EOF|_ERR)) != _READ) {
		return EOF;
	}
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL) {
			return EOF;
		}
	}
	fp->ptr = fp->base;
	fp->cnt = read(fp->fd, fp->ptr, bufsize);
	if (--fp->cnt < 0) {
		if (fp->cnt == -1) {
			fp->flag |= _EOF;
		}
		else {
			fp->flag |= _ERR;
		}
		fp->cnt = 0;
		return EOF;
	}
	return (unsigned char) *fp->ptr++;
}

int _flushbuf(int c, FILE *fp)
{
	int i, w, bufsize;

	if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE) {
		return EOF;
	}
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base == NULL) {
		if ((fp->base = (char *) malloc(bufsize)) == NULL) {
			return EOF;
		}
	}
	else if ((w = write(fp->fd, fp->base, bufsize)) <= 0) {
			if (w == 0) {
				fp->flag |= _EOF;
			}
			else {
				fp->flag |= _ERR;
			}
			fp->cnt = 0;
			return EOF;
	}
	fp->cnt = bufsize;
	for (i = 0; i < fp->cnt; i++) {
		fp->base[i] = '\0';
	}
	fp->ptr = fp->base;
	*fp->ptr = c;
	return (unsigned char) *fp->ptr++;
}

#include <string.h>

int fflush(FILE *fp)
{
	int w, bufsize;
	if ((fp->flag&(_WRITE|_EOF|_ERR)) != _WRITE) {
		return EOF;
	}
	bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
	if (fp->base != NULL && (w = write(fp->fd, fp->base, strlen(fp->base))) <= 0) {
		if (w == 0) {
			fp->flag |= _EOF;
		}
		else {
			fp->flag |= _ERR;
		}
		fp->cnt = 0;
		return EOF;
	}
	return w;
}

int fclose(FILE *fp)
{
	fflush(fp);

	fp->cnt = 0;
	fp->flag &= 0;
	if (fp->base != NULL) {
		free(fp->base);
		fp->base = fp->ptr = NULL;
	}
	fp->fd = -1;

	return 0;
}

int main()
{
	FILE *fp, *fa;
	int c;

	fp = f_open("test.txt", "r");
	fa = f_open("out.txt", "w");

	while ((c = getc(fp)) != EOF) {
		putc(c, fa);
	}
	fclose(fa);
}
