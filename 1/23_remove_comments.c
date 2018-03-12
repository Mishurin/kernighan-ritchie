/*
* Exercise 1-22. Write a program to remove all comments from a C program.
* Don't forget to handle quoted strings and characters constants properly.
* C comments do not nest.
*/

// Run test with:
// python .\runcc.py --comp gcc --sn 1.23 --opts "<" .\1\mocks\c_program_with_comments.c ">" out.c

#include <stdio.h>

int main()
{

    char ch;
    int comment_slash_detected = 0;
    int squote_open = 0;
    int dquote_open = 0;
    int sl_comment_open = 0;
    int ml_comment_open = 0;
    int closing_ml_star_detected = 0;

    while ((ch = getchar()) != EOF)
    {

        if (!sl_comment_open && !squote_open && ch == '\'')
        {
            squote_open = 1;
            putchar(ch);
            continue;
        }

        if (squote_open && ch == '\'')
        {
            squote_open = 0;
        }

        if (!sl_comment_open && !dquote_open && ch == '\"')
        {
            dquote_open = 1;
            putchar(ch);
            continue;
        }

        if (dquote_open && ch == '\"')
        {
            dquote_open = 0;
        }

        if (!squote_open && !dquote_open && (!sl_comment_open && !ml_comment_open) && !comment_slash_detected && ch == '/')
        {
            comment_slash_detected = 1;
            continue; // Skip checks to match double slashes in next iteration
        }

        if (comment_slash_detected && ch == '/')
        {
            sl_comment_open = 1;
            comment_slash_detected = 0;
        }

        if (comment_slash_detected && ch == '*')
        {
            ml_comment_open = 1;
            comment_slash_detected = 0;
        }


        if (sl_comment_open && (ch == '\r' || ch == '\n'))
        {
            sl_comment_open = 0;
        }

        if (ml_comment_open && ch == '*') {
            closing_ml_star_detected = 1;
            continue;
        }

         if (closing_ml_star_detected && ch != '/') {
            closing_ml_star_detected = 0;
            continue;
        }

        if (closing_ml_star_detected && ch == '/') {
            closing_ml_star_detected = 0;
            ml_comment_open = 0;
            continue;
        }

        if (!sl_comment_open && !ml_comment_open)
        {
            putchar(ch); // let them pass
        }
    }
    return 0;
}
