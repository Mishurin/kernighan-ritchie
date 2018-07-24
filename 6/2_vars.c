/*
* Exercise 6-2. Write a program that reads a C program and prints in alphabetical 
* order each group of variable names that are identical in the first 6 characters, 
* but different somewhere thereafter. Don't count words within strings and 
* comments. Make 6 a parameter that can be set from the command line.
*/

// Run test:
// python ./runcc.py -w --i ./6/ --inc utils.c ./2/word.c ./2/tree.c ./2/keywords.c --comp gcc --sn 6.2 -argv --opts < ./6/mocks/2_vars.c --opts 4

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "2/word.h"
#include "2/tree.h"
#include "2/keywords.h"
#define MAXWORD 100

int main(int argc, char const *argv[])
{
    if(argc != 2)
    {
        printf("error: Expected integer argument\n");
        return 1;
    }

    int cmp_limit = atoi(argv[1]);

    tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && !is_keyword(word))
            root = addtree(root, word, cmp_limit);
    //treeprint(root);
    varstobuffer(root);
    printvars();
    freetree(root);
    return 0;
}


