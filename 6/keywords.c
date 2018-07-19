#include <stdio.h>
#include <string.h>
#include "keywords.h"

char *keytab[] = {
    "auto",
    "break",
    "case",
    "char",
    "const",
    "continue",
    "default",
    "do",
    "double",
    "else",
    "enum",
    "extern",
    "float",
    "for",
    "goto",
    "if",
    "int",
    "long",
    "register",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "struct",
    "switch",
    "typedef",
    "union",
    "unsigned",
    "void",
    "volatile",
    "while"};

/* binsearch: find word in tab[0]...tab[n-1] */
char *binsearch(char *word, char *keys[], int n)
{
    int cond;
    int low, high, mid;
    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((cond = strcmp(word, keys[mid])) < 0)
            high = mid - 1;
        else if (cond > 0)
            low = mid + 1;
        else
            return keys[mid];
    }
    return NULL;
}

int is_keyword(char *word)
{
    return binsearch(word, keytab, NKEYS) != NULL;
}
