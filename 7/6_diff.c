/*
* Exercise 7-6. Write a program to compare two files, printing the first line 
* where they differ.
*/

// Compile:
// gcc -Wall ./7/6_diff.c -o ./7/6_diff
// Run test:
// ./7/6_diff ./7/mocks/6_diff1.txt  ./7/mocks/6_diff2.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000

int main(int argc, char *argv[])
{
    
    char line1[MAX_LINE_LENGTH], line2[MAX_LINE_LENGTH], *prog = argv[0];
    FILE *f1p, *f2p;

    if (argc != 3) {
        fprintf(stderr, "%s: missing arguments. Usage: diff file1 file2\n", prog);
        exit(1);
    }
    else
    {
        if ((f1p = fopen(argv[1], "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n",
                    prog, argv[1]);
            exit(1);
        }

        if ((f2p = fopen(argv[2], "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open %s\n",
                    prog, argv[2]);
            exit(1);
        }

        while (fgets(line1, MAX_LINE_LENGTH, f1p) && fgets(line2, MAX_LINE_LENGTH, f2p))
        {
            if (strcmp(line1, line2) != 0)
            {
                fprintf(stdout, "%s: Difference found:\n%s:%s%s:%s", prog, argv[1], line1, argv[2], line2);
                fclose(f1p);
                fclose(f2p);
                exit(0);
            }
        }
    }

    fprintf(stdout, "%s: no difference found\n", prog);
    fclose(f1p);
    fclose(f2p);
    exit(0);
}
