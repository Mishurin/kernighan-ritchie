#include <stdio.h>
#include <ctype.h>
#include "words.h"
#include "utils.h"

char *BLACKLIST[] = {
    "a",
    "the"};

int getword(char *word, int lim)
{
    char c;
    while (isspace(c = getch()))
        ;
    if (c != EOF)
        *word++ = c;

    if (!isalpha(c))
    {
        *word = '\0';
        return c;
    }
    for (; --lim > 0; word++)
        if (!isalnum(*word = getch()))
        {
            ungetch(*word);
            break;
        }
    *word = '\0';
    return word[0];
}

int is_word_in_black_list(char *word)
{
    return is_word_in_array(word, BLACKLIST, NKEYS);
}
