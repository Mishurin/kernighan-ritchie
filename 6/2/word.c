#include <stdio.h>
#include <ctype.h>
#include "utils.h"
#include "word.h"
#define EOL '\n'

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
    c = skip_included_lib(c);
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

/* TODO: handle conditional statements more carefully */
char skip_included_lib(char c)
{
    char temp;
    if (c == '<')
    {
        temp = getch();
        if (isalpha(temp))
        {
            while ((temp = getch()) != '>' && temp != EOL && temp != EOF)
                ;
            c = temp;
        }
        else
            ungetch(temp);
    }
    return c;
}

