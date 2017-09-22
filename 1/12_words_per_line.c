/*
* Excercise 1-12. Write a program that prints its input one word per line.
*/

#include <stdio.h>

// Run test:
// python .\runcc.py --comp gcc --sn 1.12 --opts "<" .\1\mocks\word_per_line_data.txt
int main() {

    char ch;

    while ((ch = getchar()) != EOF) {
        putchar(ch);
        if (ch == ' ' || ch == '\t') {
            putchar('\n');
        }
    }

    return 0;
}

