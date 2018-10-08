/*
* Exercise 7-7. Modify the pattern finding program of Chapter 5 to take its input
* from a set of named files or, if no files are named as arguments, from the 
* standard input. Should the file name be printed when a matching line is found?
*/

// Compile
// gcc -Wall ./7/7_find.c -o ./7/7_find
// Run test
// ./7/7_find -nx test ./7/mocks/7_find1.txt ./7/mocks/7_find2.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 1000
#define MAXPATTERN 100
#define USAGE_HINT "Usage: find -x -n pattern [file1, ...fileN]"

char line[MAXLINE];
long lineno = 0;
int found = 0;

int main(int argc, char *argv[])
{
    void prinf_matches(FILE *fp, char *fname, char *pattern, int number, int except);
    char *prog = argv[0];
    int c, except = 0, number = 0;
    while (--argc > 0 && (*++argv)[0] == '-')
        while ((c = *++argv[0]))
            switch (c)
            {
            case 'x':
                except = 1;
                break;
            case 'n':
                number = 1;
                break;
            default:
                fprintf(stderr, "find: illegal option %c\n", c);
                exit(-1);
            }

    if (argc < 1)
    {
        fprintf(stderr, "%s\n", USAGE_HINT);
        exit(0);
    }

    char pattern[MAXPATTERN];
    strcpy(pattern, *argv);
    int file = 0;
    while (*++argv)
    {
        FILE *fp;
        file = 1;
        lineno = 0;
        if ((fp = fopen(*argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n",
                    prog, *argv);
            exit(1);
        }
        prinf_matches(fp, *argv, pattern, number, except);
        fclose(fp);
    }

    if (!file)
    {
        prinf_matches(stdin, "stdin", pattern, number, except);
    }

    exit(found);
}

void prinf_matches(FILE *fp, char *fname, char *pattern, int number, int except)
{
    extern char line[MAXLINE];
    extern int found;
    extern long lineno;
    while (fgets(line, MAXLINE, fp))
    {
        lineno++;
        if ((strstr(line, pattern) != NULL) != except)
        {
            if(fp != stdin)
                printf("%s:", fname);
            if (number)
                printf("%ld:", lineno);
            printf("%s", line);
            found++;
        }
    }
}