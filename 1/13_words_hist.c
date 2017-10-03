/*
* Exercise 1-13. Write a program to print histogram of the length of words in its input.
* It is easy to draw the histogram with the bars horisontal; a vertical orientation is more
* challenging.
*/

#include <stdio.h>

#define MAX_WORD_LENGTH 1000


// Run to test:
// python .\runcc.py --comp gcc --sn 1.13 --opts "<" .\1\mocks\words_hist.txt
int main() {

    int registry[MAX_WORD_LENGTH];
    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        registry[i] = 0;
    }

    char ch;
    int chcount = 0;

    while ((ch = getchar()) != EOF) {

        if (ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ') {
            registry[chcount] += 1;
            chcount = 0;
        } else {
            chcount++;
        }
    }

    printf("Words length hist:\n");

    for (int i = 0; i < MAX_WORD_LENGTH; i++) {
        int j = registry[i];
        if (j > 0) {
            printf("%d:\t", i);
            for (int k = 1; k <= j; k++) {
                printf("|");
            }
            printf("\n");
        }
    }

    return 0;
}
