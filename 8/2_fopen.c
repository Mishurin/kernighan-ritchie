/*
* Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit 
* operations. Compare code size and execution speed.
*/

// Compile:
// gcc ./8/2_fopen.c -o ./8/2_fopen
// Run test:
// ./8/2_fopen

// Version with fields more or less as fast as without

#include <fcntl.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20
#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])
#define feof(p) (((p)->flag & _EOF) != 0)
#define ferror(p) (((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))
#define putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p))
#define getchar() getc(stdin)
#define putchar(x) putc((x), stdout)
#define PERMS 666

typedef struct flag
{
    unsigned int _READ : 1;
    unsigned int _WRITE : 1;
    unsigned int _UNBUF : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
} ffield;

typedef struct _iobuf
{
    int cnt;
    char *ptr;
    char *base;
    ffield flag;
    int fd;
} FILE;

FILE _iob[OPEN_MAX] = {
    {0, (char *)0, (char *)0, {_READ : 1}, 0},
    {0, (char *)0, (char *)0, {_WRITE : 1}, 1},
    {0, (char *)0, (char *)0, {_WRITE : 1, _UNBUF : 1}, 2}};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flag._READ || !fp->flag._WRITE)
            break;

    if (fp >= _iob + OPEN_MAX)
        return NULL;

    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1)
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    if (*mode == 'r')
        fp->flag._READ = 1;
    else
        fp->flag._WRITE = 1;
    return fp;
}

int _fillbuf(FILE *fp)
{
    int bufsize;
    if (!fp->flag._READ)
        return EOF;
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL)
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF;
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag._EOF = 1;
        else
            fp->flag._ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int main(int argc, char *argv[])
{
    system("echo $(($(date +%s%N)/1000000))");
    FILE *fp = fopen("./8/mocks/2_fopen.txt", "r");
    int buf[1];
    write(stdout->fd, buf, 1);
    if (fp)
        while ((*buf = getc(fp)) != EOF)
            write(stdout->fd, buf, 1);
    system("echo $(($(date +%s%N)/1000000))");
    return 0;
}
