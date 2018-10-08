/*
* Exercise 7-8. Write a program to print a set of files, starting each new one 
* on a new page, with a title and a running page count for each file.
*/

// Compile:
// gcc -Wall ./7/8_prinfiles.c -o ./7/8_print
// Run test:
// ./7/8_print -l 5 ./7/mocks/8_prinfile1.txt ./7/mocks/8_prinfile2.txt

#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define DEFAULT_LINES_PER_PAGE 100
#define USAGE_HINT "Usage: print [-l int] file1[, ...fileN]"

char line[MAXLINE];

int main(int argc, char *argv[])
{
    void print_file(FILE * fp, char *fname, int lines);
    char *prog = argv[0];
    int c, lines_per_page, lines_set = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'l':
                lines_set = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                exit(1);
            }

    if ((lines_set && argc < 2) || (!lines_set && argc < 1))
    {
        fprintf(stderr, "%s\n", USAGE_HINT);
        exit(0);
    }

    if (lines_set)
        sscanf(*argv, "%d", &lines_per_page);
    else
    {
        lines_per_page = DEFAULT_LINES_PER_PAGE;
        argv--;
    }

    while (*++argv)
    {
        FILE *fp;
        if ((fp = fopen(*argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n",
                    prog, *argv);
            exit(1);
        }
        print_file(fp, *argv, lines_per_page);
        fclose(fp);
    }

    return 0;
}

void print_file(FILE *fp, char *fname, int lines)
{
    extern char line[MAXLINE];
    int lines_left = lines, page = 1;
    fprintf(stdout, "<File:%s>\n", fname);
    while (fgets(line, MAXLINE, fp))
    {

        if (!lines_left)
        {
            lines_left = lines;
            fprintf(stdout, "Page:%d\n", page++);
        }

        lines_left--;

        fprintf(stdout, "%s", line);
    }

    fprintf(stdout, "<Page:%d>\n", page);
}
