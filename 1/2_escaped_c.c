/*
* Excercise 1-2. Experiment to find out what happens when printf's argument string contains "\c",
* where "c" is some character not listed above.
*/
#include <stdio.h>

int main() {
    // warning: unknown escape sequence: '\c' 
    printf("Output: \c\n");
    return 0;
}