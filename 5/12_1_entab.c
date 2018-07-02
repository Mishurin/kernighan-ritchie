/*
* Exercise 5-12. Extend entab and detab to accept the shorthand
* entab -m +n
* to mean tab stops every n columns, starting at column m. Choose convenient (for the user) 
* default behavior.
*/

// Run test
// python ./runcc.py -argv --comp gcc --sn 5.12_1 --opts +5 -5  < ./5/mocks/12_spaced_text.txt > out.txt

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_STOP 4
#define LINEMAXLEN 100

int get_line(char *s, int lim);
int get_frame(char *line, char frame[], int lim);
int get_tab_stop(int argc, char *argv[], int index);

// It is up to a text editor how big tabs should be displayed
int main(int argc, char *argv[])
{
    int length = 0;
    char line[LINEMAXLEN];
    char frame[LINEMAXLEN];

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
        int index = 1; // Apply tab stops from arg vector per each line
        char *lpt = line;
        int pos = scol;
        while (pos-- > 1)
        {
            putchar(*lpt++);
        }

        while ((length = get_frame(lpt += length, frame, tabstop)) > 0)
            printf("%s", frame);
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

int get_frame(char *lpt, char frame[], int lim)
{
    char c;
    int i;
    int trailing_space_count = 0;
    for (i = 0; i < lim && (c = *lpt++) != '\0'; i++)
    {
        if (c == ' ')
        {
            trailing_space_count++;
        }
        else if (c == '\n')
        {
            frame[i] = c;
            i++;
            break;
        }
        else
        {
            trailing_space_count = 0;
        }
        frame[i] = c;
    }

    if (trailing_space_count > 0)
    {
        int tab_index = lim - trailing_space_count;
        i = tab_index;
        frame[i] = '\t';
        i++;
    }

    frame[i] = '\0';

    return i + (trailing_space_count ? trailing_space_count - 1 : trailing_space_count);
}
