/*
* Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry.
*/

// Run test:
// gcc -Wall -g  ./8/5_fsize.c -o ./8/5_fsize
// Compile:
// ./8/5_fsize

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

void fsize(char *);

int main(int argc, char *argv[])
{
    if (argc == 1)
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

void dirwalk(char *, void (*fcn)(char *));

void fsize(char *name)
{
    struct stat stbuf;

    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        dirwalk(name, fsize);
    
    char time[100];
    struct tm *tdata = localtime(&(stbuf.st_ctime));
    strftime(time, 100, "%Y-%m-%d %H:%M:%S.000", tdata);
    printf("%8ld %s * inode:%ld * created:%s\n", stbuf.st_size, name, stbuf.st_ino, time);
}

#define MAX_PATH 1024

void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
            continue;
        if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->d_name);
        else
        {
            sprintf(name, "%s/%s", dir, dp->d_name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}
