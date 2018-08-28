/* 
* Exercise 6-6. Implement a simple version of the #define processor (i.e., no 
* arguments) suitable for use with C programs, based on the routines of this 
* section. You may also find getch and ungetch helpful.
*/

// Run test:
// python ./runcc.py -w --i ./6/ --inc utils.c --comp gcc --sn 6.6 --opts < ./6/mocks/6_defprocessor.c > out.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define EOL '\n'
#define MAXTOKEN 2000
#define MAXWORD 100
#define DEFINEKW "#define"
#define HASHSIZE 101
#define WORDTOKEN '0'
#define SYMBOLTOKEN '1'
#define COMMENTTOKEN '2'
#define SPACETOKEN '3'

int get_token(char *word, int lim);
int get_next_wtoken(char *word, int lim);

typedef struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

nlist *hashtab[HASHSIZE];

unsigned hash(char *s);
nlist *lookup(char *s);
nlist *install(char *name, char *defn);

int main(int argc, char const *argv[])
{
    char token[MAXTOKEN], name[MAXWORD], def[MAXWORD];
    nlist *fpt;
    while (get_token(token, MAXWORD) != EOF)
        if (strcmp(DEFINEKW, token) == 0)
        {
            if (get_next_wtoken(name, MAXWORD) && get_next_wtoken(def, MAXWORD))
                install(name, def);
            else
            {
                printf("%s", "error: unexpected end of file\n");
                exit(1);
            }
        }
        else if ((fpt = lookup(token)))
            printf("%s", fpt->defn);
        else
            printf("%s", token);
    return 0;
}

int get_token(char *word, int lim)
{
    int c, get_comment(char *word, int lim, char c), has_space = 0;
    char *w = word;

    while (isspace(c = getch()))
    {
        has_space = 1;
        *w++ = c;
    }

    ungetch(c);

    if (has_space)
    {
        *w = '\0';
        return SPACETOKEN;
    }

    if (get_comment(word, MAXTOKEN, (c = getch())))
        return COMMENTTOKEN;

    if (c != EOF)
        *w++ = c;
    else
        return EOF;

    if (!isalnum(c) && c != '#' && c != '_' && c != '"' && c != '\'')
    {
        *w = '\0';
        return SYMBOLTOKEN;
    }

    for (; --lim > 0; w++)
    {
        c = getch();
        if (!isalnum(c) && c != '#' && c != '_' && c != '"' && c != '\'')
        {
            ungetch(c);
            break;
        }
        else
            *w = c;
    }

    *w = '\0';

    return WORDTOKEN;
}

int get_comment(char *word, int lim, char c)
{
    char *w = word;
    if (c == '/')
    {
        c = getch();
        if (c == '/') // single line comment start
        {
            *w++ = c;
            *w++ = c;
            for (; --lim > 0; w++)
            {
                c = getch();
                if (c == EOL || c == EOF)
                {
                    ungetch(c);
                    break;
                }
                else
                    *w = c;
            }
            *w = '\0';
            return 1;
        }
        else if (c == '*') // multi line comment start
        {
            *w++ = '/';
            *w++ = '*';
            for (; --lim > 0; w++)
            {
                char nextc;
                c = *w++ = getch();
                nextc = *w = getch();
                if ((c == '*' && nextc == '/') || *w == EOF)
                {
                    if (*w == EOF)
                        ungetch(*w);
                    break;
                }
            }
            *(++w) = '\0';
            return 1;
        }
        else
            ungetch(c);
    }
    return 0;
}

int get_next_wtoken(char *word, int lim)
{
    int c;
    while((c = get_token(word, lim)) != WORDTOKEN)
        ;
    return c;
}

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

nlist *lookup(char *s)
{
    nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    return NULL;
}

nlist *install(char *name, char *defn)
{
    nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL)
    {
        np = (nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = str_dup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else
        free((void *)np->defn);
    if ((np->defn = str_dup(defn)) == NULL)
        return NULL;
    return np;
}
