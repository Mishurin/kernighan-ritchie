#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "utils.h"
#include "words.h"

static int wordscount = 0;

tnode *addtree(tnode *p, char *w)
{
    extern int wordscount;
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
        wordscount++;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
        p->count++;
    else if (cond < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);
    return p;
}

tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}

void freetree(tnode *p)
{
    if (p != NULL)
    {
        freetree(p->left);
        freetree(p->right);
        free(p->word);
        free(p);
        wordscount--;
    }
}

void treetoarr(tnode *p, tnode *arrpt[])
{
    static int i = 0;
    if (p != NULL)
    {
        arrpt[i++] = p;
        if(p->left)
            treetoarr(p->left, arrpt);
        if(p->right)
            treetoarr(p->right, arrpt);
    }
}

int cmpbywcount(tnode *a, tnode *b)
{
    if (a->count > b->count)
        return -1;
    else if (a->count < b->count)
        return 1;
    else
        return 0;
}

void print_words(tnode *root)
{
    int wcount = get_wcount();
    tnode *arroftnodes[wcount];
    treetoarr(root, arroftnodes);
    q_sort((void **)arroftnodes, 0, wcount - 1, (int (*)(void *, void *))cmpbywcount);
    for(int i = 0; i < wcount; i++)
    {
        printf("%d:%s\n", arroftnodes[i]->count, arroftnodes[i]->word);
    }
}

int get_wcount()
{
    extern int wordscount;
    return wordscount;
}