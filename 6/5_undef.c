/*
* Exercise 6-5. Write a function undef that will remove a name and definition 
* from the table maintained by lookup and install.
*/

// Run test
// python ./runcc.py -w --i ./6/ --inc utils.c --comp gcc --sn 6.5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define HASHSIZE 101

typedef struct nlist
{
    struct nlist *next;
    char *name;
    char *defn;
} nlist;

nlist *hashtab[HASHSIZE];

char *str_dup(char *);
unsigned hash(char *s);
nlist *lookup(char *s);
nlist *install(char *name, char *defn);
int undef(char *name);
void print_ht(nlist *hasht[]);

int main(int argc, char const *argv[])
{
    char *key = "a";
    char *value = "1";
    nlist *apt = install(key, value);
    install("b", "2");
    nlist *foundpt = lookup(key);
    printf("Str diff: %d\n", strcmp(value, foundpt->defn));
    printf("Pointer equallity: %d\n", apt == foundpt);
    print_ht(hashtab);
    printf("Deletion res: %d\n", undef(key));
    print_ht(hashtab);
    printf("Look up check: %d\n", lookup(key) == NULL);
    return 0;
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

int undef(char *name)
{
    nlist *np;
    nlist *prevnp = NULL;
    unsigned h = hash(name);
    for (np = hashtab[h]; np != NULL; prevnp = np, np = np->next)
        if (strcmp(name, np->name) == 0)
        {
            if (prevnp)
                prevnp->next = np->next;
            if (!np->next)
                hashtab[h] = NULL;
            free(np->name);
            free(np->defn);
            free(np);
            return 1;
        }

    return 0;
}

void print_ht(nlist *hasht[])
{
    nlist *np;
    for (int i = 0; i < HASHSIZE - 1; i++)
    {
        for (np = hasht[i]; np != NULL; np = np->next)
        {
            printf("key=%s;value=%s\n", np->name, np->defn);
        }
    }
}
