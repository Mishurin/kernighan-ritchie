/*
* Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

// Compile:
// gcc ./8/3_futils.c -o ./8/3_futils
// Run test:
// ./8/3_futils

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
#define feof(p) (((p)->flag._EOF) != 0)
#define ferror(p) (((p)->flag._ERR) != 0)
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
    {0, (char *)0, (char *)0, {_WRITE : 1, _UNBUF : 1}, 1},
    {0, (char *)0, (char *)0, {_WRITE : 1, _UNBUF : 1}, 2}};

int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (fp == NULL)
        return NULL;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if (!fp->flag._READ && !fp->flag._WRITE)
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

int _flushbuf(int c, FILE *fp)
{
    int bufsize;
    if (!fp->flag._WRITE)
        return EOF;
    
    bufsize = (fp->flag._UNBUF) ? 1 : BUFSIZ;

    if (fp->flag._UNBUF)
    {
        fp->cnt = write(fp->fd, &c, bufsize);
        if (fp->cnt == bufsize)
        {
            --fp->cnt;
            return c;
        }
        else
        {
            fp->flag._ERR = 1;
            return EOF;
        }
    }
    else
    {
        if (fp->base == NULL)
        {
            if ((fp->base = (char *)malloc(bufsize)) == NULL)
                return EOF;
            fp->ptr = fp->base;
            fp->cnt = bufsize;
        }
        else
        {
            fp->ptr = fp->base;
            fp->cnt = write(fp->fd, fp->ptr, bufsize);
            if (fp->cnt != bufsize)
            {
                fp->flag._ERR = 1;
                return EOF;
            }
            else
            {
                free(fp->base);
                fp->base = NULL;
                if ((fp->base = (char *)malloc(bufsize)) == NULL)
                    return EOF;
                fp->ptr = fp->base;
                fp->cnt = bufsize;
            }
        }
        --fp->cnt;
        return *fp->ptr++ = (unsigned char)c;
    }
}

int fflush(FILE *fp)
{
    int items;
    if (!fp->flag._WRITE)
        return EOF;
    if(fp->flag._UNBUF)
        return 0;
    items = BUFSIZ - fp->cnt;
    if (items > 0)
    {
        fp->ptr = fp->base;
        fp->cnt = write(fp->fd, fp->ptr, items);
        if (fp->cnt != items)
        {
            fp->flag._ERR = 1;
            return EOF;
        }
        else
        {
            fp->cnt = 0;
            free(fp->base);
            fp->base = NULL;
            fp->ptr = fp->base;
            return items;
        }
    }
    else
        return 0;
}

int fclose(FILE *fp)
{
    if(fp->flag._WRITE)
        fflush(fp);
    return close(fp->fd);
}

int main(int argc, char *argv[])
{
    system("echo $(($(date +%s%N)/1000000))");
    FILE *fp = fopen("./8/mocks/3_futils.txt", "r");
    FILE *fw = fopen("./8/out.txt", "w");
    int c;
    if (fp)
        while ((c = getc(fp)) != EOF)
        {
            putc(c, fw);
            putchar(c);
        }
    putchar('\n');
    fclose(fw);
    system("echo $(($(date +%s%N)/1000000))");
    system("diff ./8/mocks/3_futils.txt ./8/out.txt");
    return 0;
}
