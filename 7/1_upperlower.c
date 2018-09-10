/*
* Exercise 7-1. Write a program that converts upper case to lower or lower case 
* to upper, depending on the name it is invoked with, as found in argv[0].
*/

// Run test:
// gcc ./7/1_upperlower.c -o ./7/upper
// ./7/upper
// gcc ./7/1_upperlower.c -o 
// ./7/lower

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int c;
    int (*fn)(int c);
    
    if (strstr(argv[0], "upper") != NULL)
    {
        fn = toupper;
    }
    else if (strstr(argv[0], "lower") != NULL)
    {
        fn = tolower;
    }
    else
    {
        exit(1);
    }

    putchar('\n');

    while ((c = getchar()) != EOF)
        putchar(fn(c));
    return 0;
}
