/*
* Exercise 6-3. Write a cross-referencer that prints a list of all words in a 
* document, and for each word, a list of the line numbers on which it occurs. 
* Remove noise words like ``the,'' ``and,'' and so on.
*/

// Run test:
// python ./runcc.py -w --i ./6/ --inc utils.c ./3/words.c ./3/tree.c --comp gcc --sn 6.3 --opts < ./6/mocks/3_crossreferencer.txt

#include <stdio.h>
#include <ctype.h>
#include "3/words.h"
#include "3/tree.h"

#define MAXWORD 100


int main(int argc, char const *argv[])
{
    char c;
    char word[MAXWORD];
    tnode *root = NULL;
    while ((c = getword(word, MAXWORD)) != EOF)
        if ((isalpha(word[0])) && !is_word_in_black_list(word))
            root = addtree(root, word, getlinenum());
    treeprint(root);
    freetree(root);
    return 0;
}
