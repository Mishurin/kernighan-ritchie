/*
* Exercise 1-22. Write a program to check a C program for rudimentary syntax
* errors like unbalanced parentheses, brackets and braces. Don't forget about
* quotes, both single and double, escape sequences, and comments.
*/

// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\1_round_parentheses__invalid ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\2_round_parentheses__valid ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\3_curly_parentheses__invalid ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\5_square_parentheses__invalid ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\6_square_parentheses__valid ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\7_single_quotes__invalid.c ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\8_single_quotes_valid.c ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\9_double_quotes_invalid.c ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\10_double_quotes_valid.c ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\11_escape_sequence_invalid.c ">" out
// python .\runcc.py --comp gcc --sn 1.24 --opts "<" .\1\mocks\24_programs\12_escape_sequence_valid.c ">" out

#include <stdio.h>

// there are few more however sequences allowed
#define ESCAPE_SEQUENCES_ARR_LENGTH 12

char ESCAPE_SEQUENCES[ESCAPE_SEQUENCES_ARR_LENGTH] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '\'', '\"', '?', 'e'};

int is_allowed_escape_sequence(char ch);

int main()
{
    char ch;
    int rbraces_open = 0;
    int rbraces_close = 0;
    int cbraces_open = 0;
    int cbraces_close = 0;
    int sbraces_open = 0;
    int sbraces_close = 0;
    int comment_slash_found = 0;
    int ml_comment_open = 0;
    int sl_comment_open = 0;
    int comment_star_found = 0;
    int scomma_open = 0;
    int dcomma_open = 0;
    int escape_sequence_open = 0;
    int is_valid = 1;

    printf("---Report--\n");

    while ((ch = getchar()) != EOF)
    {

        if (!comment_slash_found && !comment_star_found && !scomma_open && !dcomma_open && ch == '/')
        {
            comment_slash_found = 1;
            continue;
        }

        if (comment_slash_found && ch == '*')
        {
            ml_comment_open = 1;
            comment_slash_found = 0;
            continue;
        }

        if (comment_slash_found && ch == '/')
        {
            sl_comment_open = 1;
            comment_slash_found = 0;
            continue;
        }

        if (!comment_star_found && ml_comment_open && ch == '*')
        {
            comment_star_found = 1;
            continue;
        }

        if (comment_star_found && ch == '/')
        {
            ml_comment_open = 0;
            comment_star_found = 0;
            continue;
        }

        if (!scomma_open && !ml_comment_open && !sl_comment_open && ch == '\'')
        {
            scomma_open = 1;
            continue;
        }

        if (scomma_open && ch == '\'')
        {
            scomma_open = 0;
            continue;
        }

        if (!dcomma_open && !ml_comment_open && !sl_comment_open && ch == '\"')
        {
            dcomma_open = 1;
            continue;
        }

        if (dcomma_open && ch == '\"')
        {
            dcomma_open = 0;
            continue;
        }

        if ((dcomma_open || scomma_open) && ch == '\n')
        {
            printf("Unexpected line break in the middle of the string literal\n");
            scomma_open = 0;
            dcomma_open = 0;
            continue;
        }

        if ((dcomma_open || scomma_open) && ch == '\\')
        {
            escape_sequence_open = 1;
            continue;
        }

        if (escape_sequence_open && is_allowed_escape_sequence(ch))
        {
            escape_sequence_open = 0;
            continue;
        }

        if (escape_sequence_open && !is_allowed_escape_sequence(ch))
        {
            escape_sequence_open = 0;
            printf("Not allowed escape sequence.");
            continue;
        }

        if (sl_comment_open && ch == '\n')
        {
            sl_comment_open = 0;
            continue;
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

    if (rbraces_open != rbraces_close)
    {
        is_valid = 0;
        printf("() Mismatch: %d '(' against %d ')\n", rbraces_open, rbraces_close);
    }

    if (cbraces_open != cbraces_close)
    {
        is_valid = 0;
        printf("{} Mismatch: %d '{' against %d '}\n", cbraces_open, cbraces_close);
    }

    if (sbraces_open != sbraces_close)
    {
        is_valid = 0;
        printf("[] Mismatch: %d '[' against %d ']\n", sbraces_open, sbraces_close);
    }

    if (ml_comment_open)
    {
        is_valid = 0;
        printf("Multiline comment is not closed");
    }

    if (is_valid)
    {
        printf("Valid\n");
    }

    return 0;
}

int is_allowed_escape_sequence(char ch)
{
    int res = 0;
    extern char ESCAPE_SEQUENCES[];
    for (int i = 0; i < ESCAPE_SEQUENCES_ARR_LENGTH; i++)
    {
        if (ch == ESCAPE_SEQUENCES[i])
        {
            res = 1;
            break;
        }
    }
    return res;
};