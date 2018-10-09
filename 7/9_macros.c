/*
* Exercise 7-9. Functions like isupper can be implemented to save space or to 
* save time. Explore both possibilities.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 7.9

#include <stdio.h>
#include <stdlib.h>
#define isup(x) (x >= 'A' && x <= 'Z')
// Version with pointers is not needed but possible
#define isupp(x) (*x >= 'A' && *x <= 'Z')

int main(int argc, char const *argv[])
{
    char a = 'a';
    char b = 'z';
    char c = 'A';
    char d = 'Z';
    char e = '@';

    // Using macros saves memory (no additional stack memory allocated for 
    // function calls and variables copies) and speeds up program (no function calls)
    printf("%c is %s\n", a, isup(a) == 1 ? "upper" : "lower");
    printf("%c is %s\n", b, isup(b) == 1 ? "upper" : "lower");
    printf("%c is %s\n", c, isup(c) == 1 ? "upper" : "lower");
    printf("%c is %s\n", d, isup(d) == 1 ? "upper" : "lower");
    printf("%c is %s\n", e, isup(e) == 1 ? "upper" : "not upper");
    printf("%c is %s\n", a, isupp(&a) == 1 ? "upper" : "lower");
    printf("%c is %s\n", b, isupp(&b) == 1 ? "upper" : "lower");
    printf("%c is %s\n", c, isupp(&c) == 1 ? "upper" : "lower");
    printf("%c is %s\n", d, isupp(&d) == 1 ? "upper" : "lower");
    printf("%c is %s\n", e, isupp(&e) == 1 ? "upper" : "not upper");
    return 0;
}
