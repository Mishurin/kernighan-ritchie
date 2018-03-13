/*
* Exercise 1-22. Write a program to check a C program for rudimentary syntax
* errors like unbalanced parentheses, brackets and braces. Don't forget about
* quotes, both single and double, escape sequences, and comments.
*/

#include <stdio.h>

int main()
{
    char ch;
    int line_number = 0;
    int rbraces_open = 0;
    int rbraces_close = 0;
    int cbraces_open = 0;
    int cbraces_close = 0;
    int sbraces_open = 0;
    int sbraces_close = 0;
    int is_valid = 1;

    while ((ch = getchar()) != EOF)
    {

        if (ch == '\n')
        {
            printf("%d\n", line_number);
            line_number++;
        }

        if (ch == '(')
        {
            rbraces_open++;
        }

        if (ch == ')')
        {
            rbraces_close++;
        }

        if (ch == '{')
        {
            cbraces_open++;
        }

        if (ch == '}')
        {
            cbraces_close++;
        }

        if (ch == '[')
        {
            sbraces_open++;
        }

        if (ch == ']')
        {
            sbraces_close++;
        }
    }

    printf("%d\n", line_number);

    if (rbraces_open != rbraces_close)
    {
        is_valid = 0;
        printf("() Mismatch: %d '(' against %d ')\n", rbraces_open, rbraces_close );
    }

    if (sbraces_open != sbraces_close)
    {
        is_valid = 0;
        printf("[] Mismatch: %d '[' against %d ']\n", sbraces_open, sbraces_close );
    }

    if(sbraces_open != sbraces_close)
    {
        is_valid = 0;
        printf("{} Mismatch: %d '{' against %d '}\n", cbraces_open, cbraces_close );
    }

    if(is_valid) {
        printf("Valid\n");
    }

    return 0;
}