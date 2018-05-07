/*
* Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower 
* case, with a conditional expression instead of if-else.
*/

#include <stdio.h>
#include <string.h>

// Run test:
// python ./runcc.py --comp gcc --sn 2.10

int lower(int c)
{
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main()
{
    char test[] = "TEST";
    for(int i = 0; i < sizeof(test); i++) {
        test[i] = lower(test[i]);
    }
    printf("%s\n", test);
}
