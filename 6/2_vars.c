/*
* Exercise 6-2. Write a program that reads a C program and prints in alphabetical 
* order each group of variable names that are identical in the first 6 characters, 
* but different somewhere thereafter. Don't count words within strings and 
* comments. Make 6 a parameter that can be set from the command line.
*/

// Run test:
// python ./runcc.py -w --i ./6/ --inc ./utils.c ./word.c ./tree.c ./keywords.c --comp gcc --sn 6.2 -argv --opts < ./6/mocks/1_getword.c --opts 7

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "word.h"
#include "tree.h"
#include "keywords.h"
#define MAXWORD 100

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("error: Expected integer argument\n");
        return 1;
    }

    int cmp_limit = atoi(argv[0]);

    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && !is_keyword(word))
            root = addtree(root, word);
    treeprint(root);
    return 0;
    return 0;
}


