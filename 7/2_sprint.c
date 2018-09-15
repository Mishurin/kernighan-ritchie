/*
* Exercise 7-2. Write a program that will print arbitrary input in a sensible way. 
* As a minimum, it should print non-graphic characters in octal or hexadecimal 
* according to local custom, and break long text lines.
*/

// Run test:
// gcc -Wall ./7/2_sprint.c -o ./7/sprint
// ./7/sprint -o -l 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char const *argv[])
{
    void print_oct(int c);
    void print_hex(int c);
    void print_def(int c);
    int get_line(char *s, int lim);
    void print_line(char *line, void (*fn)(int c));

    void (*fn)(int c) = print_def;
    int lim = 0;

    while (*++argv != NULL)
    {
        if (strcmp(*argv, "-o") == 0)
            fn = print_oct;
        if (strcmp(*argv, "-x") == 0)
            fn = print_hex;
        if (strcmp(*argv, "-l") == 0)
        {
            argv++;
            if (*argv == NULL)
            {
                printf("%s\n", "warning: expected limit value");
                exit(1);
            }
            else
            {
                lim = atoi(*argv);
            }
        }
    }

    lim = lim ? lim : MAX_LINE_LENGTH;
    char line[lim + 1];

    while (get_line(line, lim + 1))
        print_line(line, fn);
    return 0;
}

void print_oct(int c)
{
    printf("o%o", c);
}

void print_hex(int c)
{
    printf("x%x", c);
}

void print_def(int c)
{
    printf("%c", c);
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

void print_line(char *line, void (*fn)(int c))
{
    while (*line != '\0')
    {
        if (*line < ' ' || *line > '~')
            fn(*line);
        else
            putchar(*line);
        line++;
    }
    putchar('\n');
}
