/*
* Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and 
* close instead of their standard library equivalents. Perform experiments to determine 
* the relative speeds of the two versions.
*/

// Compile:
// gcc -Wall ./8/cat_v1.c -o ./8/cat_v1
// Run test:
// ./8/cat_v1 ./8/mocks/1_cat1.txt ./8/mocks/1_cat2.txt

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    system("echo $(($(date +%s%N)/1000000))");
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0];

    if (argc == 1)
        filecopy(stdin, stdout);
    else
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "%s: can't open %s\n",
                        prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    system("echo $(($(date +%s%N)/1000000))");
    exit(0);
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}