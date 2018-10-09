/*
* Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and 
* close instead of their standard library equivalents. Perform experiments to determine 
* the relative speeds of the two versions.
*/

// Compile:
// gcc -Wall ./8/1_cat.c -o ./8/1_cat
// Run test:
// ./8/1_cat ./8/mocks/1_cat1.txt ./8/mocks/1_cat2.txt

// This version is a bit faster

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/syscall.h>

void error(char *, ...);

int main(int argc, char *argv[])
{
    system("echo $(($(date +%s%N)/1000000))");
    void filecopy(int idesc, int odesc, char buf[BUFSIZ], char *pname);
    char buf[BUFSIZ], *prog = argv[0];
    int fd;
    if (argc == 1)
        filecopy(0, 1, buf, prog);
    else
        while (*++argv)
            if ((fd = open(*argv, O_RDONLY, 0)) == -1)
                error("%s: can't open %s", prog, *argv);
            else
            {
                filecopy(fd, 1, buf, prog);
                close(fd);
            }
    system("echo $(($(date +%s%N)/1000000))");
    exit(0);
}

void filecopy(int idesc, int odesc, char buf[BUFSIZ], char *pname)
{
    int n;
    while ((n = read(idesc, buf, BUFSIZ)) > 0)
        if (write(odesc, buf, n) != n)
            error("%s: write error on stdout", pname);
}

void error(char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
