/*
* Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to 
* accept a list of tab stops as arguments. Use the default tab settings if there are no 
* arguments.
*/

// Run test:
// python ./runcc.py -argv --comp gcc --sn 5.11_2 --opts 5 6  < ./5/mocks/11_tabbed_text.txt > out.txt

#include <stdio.h>
#include <stdlib.h>
#define DEFAULT_TAB_STOP 4
#define LINEMAXLEN 100

int get_line(char *s, int lim);
int get_tab_stop(int argc, char *argv[], int index);
void insert_spaces(int times);
int get_frame(char *fstart, int lim);

int main(int argc, char *argv[])
{
    char line[LINEMAXLEN];

    while (get_line(line, LINEMAXLEN) > 0)
    {
        int index = 1; // Apply tab stops from arg vector per each line
        char *lpt = line;
        int length = 0;

        while ((length = get_frame(lpt += length, get_tab_stop(argc, argv, index++))) > 0)
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

int get_tab_stop(int argc, char *argv[], int index)
{
    if (argc == 1 || index >= argc)
        return DEFAULT_TAB_STOP;
    else
    {
        return atoi(argv[index]);
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