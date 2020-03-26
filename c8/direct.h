#define NAME_MAX 14

typedef struct {
	long ino;
	char name[NAME_MAX];
} Dirent;

typedef struct {
	int fd;
	Dirent d;
} DIRX;

DIRX *open_dir(char *dirname);
Dirent *read_dir(DIRX *dfd);
void close_dir(DIRX *dfd);
