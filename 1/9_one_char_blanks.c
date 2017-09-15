/*
* Excercise 1-9. Write a program to copy its input to its output, replacing each string of
* one ore more blanks by a single blank.
*/

#include <stdio.h>

int main() {

    int spaced = 0;

    char c;

    while ((c = getchar()) != EOF) {

        if (c == ' ') {

            if (spaced) {
                ;
            } else {
                putchar(c);
                spaced = 1;
            }

        } else {
            spaced = 0;
            putchar(c);
        }
    }

    return 0;
}