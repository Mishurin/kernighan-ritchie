#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "utils.h"
/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, char *w, int n)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strncmp(w, p->word, n)) == 0)
    {
        if (strcmp(w, p->word) == 0)
            p->count++;
        if (!find_in_llist(w, p->words))
            addllnode(w, &p->words, &p->wcount);
    }
    else if (cond < 0)
        p->left = addtree(p->left, w, n);
    else
        p->right = addtree(p->right, w, n);
    return p;
}

/* treeprint: in-order print of tree p */
void treeprint(tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

/* talloc: make a tnode */
tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}

#define RESARRMAXLENGTH 1000
char *vars[RESARRMAXLENGTH];
static int wadded = 0;
void printvars()
{
     q_sort((void **)vars, 0, wadded -1, (int (*)(void *, void *))strcmp);
    char **wstartpt = vars;
    while (*wstartpt)
    {
        printf("%s\n", *wstartpt++);
    }
}

void varstobuffer(tnode *p)
{
    static char **wpt = vars;
    extern int wadded;
    if (p != NULL)
    {
        varstobuffer(p->left);
        if (p->wcount && (wadded + p->wcount) <= RESARRMAXLENGTH)
        {
            llisttoarray(p->words, wpt);
            wpt += p->wcount;
            wadded += p->wcount;
        }
        varstobuffer(p->right);
    }
}

void freetree(tnode *p)
{
    if (p != NULL)
    {
        freetree(p->left);
        freetree(p->right);
        if (p->words)
            freellist(&p->words, &p->wcount);
        free(p);
    }
}

llnode *addllnode(char *word, llnode **head, int *count)
{
    llnode *new = malloc(sizeof(llnode));
    if (new)
    {
        new->word = str_dup(word);
        new->next = *head;
        *head = new;
        (*count)++;
        return new;
    }
    else
    {
        *count = 0;
        freellist(head, count);
        return NULL;
    }
}

llnode *removellnode(llnode **head, int *count)
{
    llnode *temp = *head;
    *head = temp->next;
    free(temp->word);
    free(temp);
    (*count)--;
    return *head;
}

int freellist(llnode **head, int *count)
{
    while (removellnode(head, count))
        ;
    return *head == NULL;
}

int find_in_llist(char *word, llnode *head)
{
    while (head)
    {
        if (strcmp(head->word, word) == 0)
            return 1;
        head = head->next;
    }
    return 0;
}

void llisttoarray(llnode *head, char *words[])
{
    char **pt = words;
    while (head)
    {
        *pt = head->word;
        pt++;
        head = head->next;
    }
}

/* make a duplicate of s */
char *str_dup(char *s)
{
    char *p;
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
        strcpy(p, s);
    return p;
}