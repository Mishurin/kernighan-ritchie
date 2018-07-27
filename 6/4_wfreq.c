/*
* Exercise 6-4. Write a program that prints the distinct words in its input 
* sorted into decreasing order of frequency of occurrence. Precede each word by 
* its count.
*/

// Run test:
// python ./runcc.py -w --i ./6/ --inc utils.c ./4/words.c ./4/tree.c --comp gcc --sn 6.4 --opts < ./6/mocks/4_wfreq.txt

#include <stdio.h>
#include <ctype.h>
#include "4/words.h"
#include "4/tree.h"

#define MAXWORD 100

int main(int argc, char const *argv[])
{
    char c;
    char word[MAXWORD];
    tnode *root = NULL;
    while ((c = getword(word, MAXWORD)) != EOF)
        if ((isalpha(word[0])) && !is_word_in_black_list(word))
            root = addtree(root, word);
    print_words(root); // Prints words sorted by frequency but not sorted alphabetically
    freetree(root);
    return 0;
}