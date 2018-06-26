/*
* Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than 
* calling alloc to maintain storage. How much faster is the program?
*/

// Run test:
//python ./runcc.py --comp gcc --i ./5/utils/ --inc ./utils/6_utils.c --sn 5.7 --opts < ./5/mocks/7_readlines

#include <stdio.h>
#include <string.h>
#include "6_utils.h"
#define MAXLINES 5000    /* max #lines to be sorted */
#define MAXLEN 1000      /* max length of any input line */
#define MAXSTACKLEN MAXLINES * MAXLEN

char *lineptr[MAXLINES]; /* pointers to text lines */

// No extra costs except for function call and extra memort to store
// copies of local param values. Just guess.
int readlines(char *[], int, char *);

int main()
{
    int nlines;
    char stack[MAXSTACKLEN];
    char **ptr = lineptr;
    /* number of input lines read */
    if ((nlines = readlines(lineptr, MAXLINES, stack)) >= 0)
    {
        while(nlines-- > 0)
        {
            printf("%s\n", *ptr++);
        }
        return 0;
    }
    else
    {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines, char *stack)
{
    int len, nlines;
    char *sp = stack, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines ||  stack + MAXSTACKLEN - sp < len)
            return -1;
        else
        {
            line[len - 1] = '\0'; /* delete newline */
            strcpy(sp, line);
            lineptr[nlines++] = sp;
            sp += len;
        }
    return nlines;
}