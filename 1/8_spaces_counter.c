/*
* Excercise 1-8. Write a program to count blanks, tabs, and newlines.
*/

#include <stdio.h>

int main () {

    int scount, tcount, ncount;

    scount = tcount = ncount = 0;
    
    char c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            scount++;
        } else if (c == '\t') {
            tcount++;
        } else if (c == '\n') {
            ncount++;
        }
    }

    printf("Statistics: \n");
    printf("Spaces: %d\n", scount);
    printf("Tabs: %d\n", tcount);
    printf("New lines: %d\n", ncount);

    return 0;
}
