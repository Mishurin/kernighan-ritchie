/*
* Exercise 1-20. Write a program detab that replaces tabs in the input
* with the proper number of blanks to space to the next tab stop. Assume
* a fixed set of tab stops, say every n columns. Sould n be a variable or
* a symbolic parameter?
*/

#include <stdio.h>
#define TAB_SIZE 4
// [1|2|3|4][1|2|3|->][1|2|-->][1|--->][---->]
// [1|2|3|4][1|2|3|s][1|2|s|s][1|s|s|s][s|s|s|s]

void insert_spaces(int times);
int col = 1;
// Run to test:
// python .\runcc.py --comp gcc --sn 1.20 --opts "<" .\1\mocks\tabbed_text.txt">" out.txt
int main() {
    char ch;
    extern int col;
    while ((ch = getchar()) != EOF) {
        if (ch == '\t') {
            insert_spaces(TAB_SIZE - ((col - 1) % TAB_SIZE));
        } else if (ch == '\n') {
            putchar('\n');
            col = 1;
        } else if (ch == '\r') {
            putchar('\r');
        } else {
            putchar(ch);
            col++;
        }
    }
    return 0;
}

void insert_spaces(int times) {
    extern int col;
    for (int i = 0; i < times; i++) {
        putchar(' ');
        col++;
    }
}