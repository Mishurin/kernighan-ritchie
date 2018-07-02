/*
* Exercise 5-11. Modify the program entab and detab (written as exercises in Chapter 1) to 
* accept a list of tab stops as arguments. Use the default tab settings if there are no 
* arguments.
*/

// Run test
// python ./runcc.py -argv --comp gcc --sn 5.11_1 --opts 5 6  < ./5/mocks/11_spaced_text.txt > out.txt

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

    while (get_line(line, LINEMAXLEN) > 0)
    {
        int index = 1; // Apply tab stops from arg vector per each line
        char *lpt = line;
        while ((length = get_frame(lpt += length, frame, get_tab_stop(argc, argv, index++))) > 0)
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

    return i + (trailing_space_count? trailing_space_count - 1 : trailing_space_count);
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

