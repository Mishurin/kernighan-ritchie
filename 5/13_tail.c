/*
* Exercise 5-13. Write the program tail, which prints the last n lines of its input. By 
* default, n is set to 10, let us say, but it can be changed by an optional argument so
* that
* tail -n
* prints the last n lines. The program should behave rationally no matter how unreasonable 
* the input or the value of n. Write the program so it makes the best use of available 
* storage; lines should be stored as in the sorting program of Section 5.6, not in a 
* two-dimensional array of fixed size.
*/

// Run test:
// python ./runcc.py -argv --comp gcc --sn 5.13 --opts -5  < ./5/mocks/13_tail.txt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXLINES 5000
#define MAXLEN 1000
#define MAXSTACKLEN MAXLINES * MAXLEN
#define DEFAULT_TAIL_SIZE 10

char *lineptr[MAXLINES];

int readlines(char *[], int, char *);
int get_line(char *s, int lim);

int main(int argc, char *argv[])
{
    int nlines;
    char stack[MAXSTACKLEN];
    char **ptr = lineptr;

    int n = DEFAULT_TAIL_SIZE;
    while (*++argv != NULL)
    {
        if (*argv[0] == '-')
        {
            n = atoi(*argv + 1);
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES, stack)) >= 0)
    {
        ptr += nlines >= n ? nlines - n : 0;
        nlines = nlines >= n ? n : nlines;
        while (nlines-- > 0)
        {
            printf("%s\n", *ptr++);
        }
        return 0;
    }
    else
    {
        printf("error: input is too big\n");
        return 1;
    }
}

int readlines(char *lineptr[], int maxlines, char *stack)
{
    int len, nlines;
    char *sp = stack, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || stack + MAXSTACKLEN - sp < len)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(sp, line);
            lineptr[nlines++] = sp;
            sp += len;
        }
    return nlines;
}

int get_line(char *s, int lim)
{
    int c, i;

    for (i = 0; --lim && (c = getchar()) != EOF && c != '\n'; s++, i++)
    {
        *s = c;
    }

    if (c == '\n')
    {
        *s++ = c;
        i++;
    }

    *s = '\0';
    return i;
}
