/*
* Excercise 1-9. Write a program to copy its input to its output, replacing each string of
* one ore more blanks by a single blank.
*/

#include <stdio.h>

int main() {

    int scount = 0;

    char c;

    while ((c = getchar()) != EOF) {

        if (c == ' ') {

            if (scount == 0) {
                putchar(c);
            } else {
                scount = 0;
            }

            scount++;
            
        } else {
            scount = 0;
            putchar(c);
        }
    }

    return 0;
}