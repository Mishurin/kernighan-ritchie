/*
* Exercise 6-1. Our version of getword does not properly handle underscores, 
* string constants, comments, or preprocessor control lines. Write a better 
* version.
*/

// Run test
// python ./runcc.py -w --i ./6/ --inc ./utils.c --comp gcc --sn 6.1 --opts < ./6/mocks/1_getword.c

#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#define WORLDLENGTHLIM 100
#define EOL '\n'
int getword(char *word, int lim);
char skip_string_consts(char);
char skip_comments(char);

int main()
{
    char word[100];

    while (getword(word, WORLDLENGTHLIM) != EOF)
    {
        printf("%s\n", word);
    }
    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()))
        ;
    c = skip_string_consts(c);
    c = skip_comments(c);
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '#' && c != '_')
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_')
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

char skip_string_consts(char c)
{
    if (c == '\"')
        while ((c = getch() != '\"' && c != EOL && c != EOF))
            ;
    return c;
}

char skip_comments(char c)
{
    if (c == '/')
    {
        c = getch();
        if (c == '/') // single line comment start
        {
            while ((c = getch()) != EOL && c != EOF)
                ;
            c = getch();
        }
        else if (c == '*') // multi line comment start
        {
            while (!((c = getch()) == '*' && (c = getch()) == '/') && c != EOF)
                ;
            c = getch();
        }
        else
            ungetch(c);
    }
    return c; // returning last read char
}
