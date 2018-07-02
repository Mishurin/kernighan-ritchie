/*
* Exercise 5-12. Extend entab and detab to accept the shorthand
* entab -m +n
* to mean tab stops every n columns, starting at column m. Choose convenient (for the user) 
* default behavior.
*/

// Run test:
// python ./runcc.py -argv --comp gcc --sn 5.12_2 --opts +5 -3  < ./5/mocks/12_tabbed_text.txt > out.txt

#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TAB_STOP 4
#define LINEMAXLEN 100

int get_line(char *s, int lim);
void insert_spaces(int times);
int get_frame(char *fstart, int lim);

int main(int argc, char *argv[])
{
    char line[LINEMAXLEN];

    int scol = 0;
    int tabstop = DEFAULT_TAB_STOP;
    while (*++argv != NULL)
    {
        if (*argv[0] == '-')
        {
            scol = atoi(*argv + 1);
        }
        if (*argv[0] == '+')
        {
            tabstop = atoi(*argv + 1);
        }
    }

    while (get_line(line, LINEMAXLEN) > 0)
    {
        char *lpt = line;
        int length = 0;

        int pos = scol;
        while (pos-- > 1)
        {
            putchar(*lpt++);
        }

        while ((length = get_frame(lpt += length, tabstop)) > 0)
            ;
    }

    return 0;
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

void insert_spaces(int times)
{
    for (int i = 0; i < times; i++)
    {
        putchar(' ');
    }
}

int get_frame(char *fstart, int lim)
{
    char c;
    int i;
    for (i = 0; i < lim && (c = *fstart++) != '\0'; i++)
    {
        if (c == '\t')
        {
            insert_spaces(lim - i);
            i++;
            break;
        }
        else
            putchar(c);
    }
    return i;
}