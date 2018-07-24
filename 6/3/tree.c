#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"
#include "utils.h"
#include "words.h"

tnode *addtree(tnode *p, char *w, int line)
{
    int cond;
    if (p == NULL)
    {
        p = talloc();
        p->word = str_dup(w);
        p->count = 1;
        p->left = p->right = NULL;
        addllnode(line, &p->lines, &p->tail);
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        p->count++;
        llnode *lllnodept = find_in_llist(line, p->lines);
        if (lllnodept)
            lllnodept->count++;
        else
            addllnode(line, &p->lines, &p->tail);
    }
    else if (cond < 0)
        p->left = addtree(p->left, w, line);
    else
        p->right = addtree(p->right, w, line);
    return p;
}

tnode *talloc(void)
{
    return (tnode *)malloc(sizeof(tnode));
}

llnode *find_in_llist(int line, llnode *head)
{
    while (head)
    {
        if (head->line == line)
            return head;
        head = head->next;
    }
    return NULL;
}

llnode *addllnode(int line, llnode **head, llnode **tail)
{
    llnode *new = malloc(sizeof(llnode));
    if (new)
    {
        if(!*head)
            *head = new;
        else if(!(*head)->next)
            (*head)->next = new;
        if(!*tail)
            *tail = new;
        else {
            new->next = NULL;
            new->prev = *tail;
            *tail = new;
        }
        new->line = line;
        new->count = 1;
        return new;
    }
    else
    {
        freellist(*head);
        return NULL;
    }
}

void freellist(llnode *head)
{
    if (head != NULL)
    {
        freellist(head->next);
        free(head);
    }
}

llnode *removellnode(llnode **head)
{
    llnode *temp = *head;
    *head = temp->next;
    free(temp);
    return *head;
}

void treeprint(tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s:", p->count, p->word);
        llnode *head = p->lines;
        while (head)
        {
            printf("(line: %d, times: %d);", head->line, head->count);
            head = head->next;
        }
        printf("%c", EOL);
        treeprint(p->right);
    }
}

void freetree(tnode *p)
{
    if (p != NULL)
    {
        freetree(p->left);
        freetree(p->right);
        freellist(p->lines);
        free(p->word);
        free(p);
    }
}
