/*
* Exercise 1-22. Write a program to "fold" long input lines into to or more shorter
* lines after the last non-blank characters that occurs before the n-th column
* of input. Make sure your program does something intelligent with very long lines,
* and if there are no blanks or tabs before the specified column.
*/

// Run test with:
// python .\runcc.py --comp gcc --sn 1.22 --opts "<" .\1\mocks\text_to_wrap.txt ">" out.txt

#include <stdio.h>
#define MAX_LINE_LENGTH 10
#define TAB_SIZE 4
#define WIN_MODE 1

void print_buffer(char buffer[], int buffer_length);

int main()
{
    char ch;
    int col = 1;
    int was_unbreakable_tab_found = 0;
    char tab_buffer[TAB_SIZE + 1];
    int tab_buffer_position = 0;

    while ((ch = getchar()) != EOF)
    {

        if (ch == '\r' || ch == '\n')
        {
            putchar(ch);
            col = 1;
            continue;
        }

        if (col > MAX_LINE_LENGTH)
        {

            if (WIN_MODE)
            {
                putchar('\r');
                putchar('\n');
            }
            else
            {
                putchar('\n');
            }

            col = 1;

            if (was_unbreakable_tab_found)
            {
                print_buffer(tab_buffer, TAB_SIZE);
                tab_buffer_position = 0;
                was_unbreakable_tab_found = 0;
                col += TAB_SIZE;
            }

        }

        if (ch == '\t' &&
            (col > (MAX_LINE_LENGTH - TAB_SIZE) || col <= MAX_LINE_LENGTH - TAB_SIZE))
        {
            was_unbreakable_tab_found = 1;
            continue;
        }

        if (was_unbreakable_tab_found)
        {
            putchar(' ');
            col++;
            tab_buffer[tab_buffer_position] = ch;
            tab_buffer_position++;
            continue;
        }

        putchar(ch);
        col++;
    }

    return 0;
}

void print_buffer(char buffer[], int buffer_length)
{
    buffer[buffer_length] = '\0';
    printf(buffer);
    for (int i = 0; i < buffer_length; i++)
    {
        buffer[i] = '\0';
    }
}
