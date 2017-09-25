/*
* Excercise 1-14. Write a program to print a histogram of the frequencies
* of different characters in its input.
*/

#include <stdio.h>

#define ASCII_MAX 255

// Run to test:
// python .\runcc.py --comp gcc --sn 1.14 --opts "<" .\1\mocks\char_frequency.txt

int main() {
    
    int registry[ASCII_MAX];
    for (int i = 0; i <= ASCII_MAX; i++) {
        registry[i] = 0;
    }

    char ch;

    while ((ch = getchar()) != EOF) {
        if(!(ch == '\n' || ch == '\r' || ch == '\t' || ch == ' ')) {
            registry[ch] += 1;
        }
    }

    for (int i = 0; i <= 255; i++) {
        int k = registry[i];
        if (k > 0) {
            printf("%c:\n", i);
            for (int j = 1; j <= k; j++) {
                printf("|");
            }
            printf("\n");
        }
    }

    return 0;
}