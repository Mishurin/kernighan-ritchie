/*
* Exercise 1-6. Verify that the expression getchar() != EOF is 0 or 1.
*/

#include <stdio.h>

int main() {
    printf("Enter character(s) or hit CTRL^D\n");
    printf("Result: %d\n", getchar() != EOF);
    return 0;
}
