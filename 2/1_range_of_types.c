/*
* Exercise 2-1. Write a program to determine the ranges of char, short, int,
* and long variables, both signed and unsigned, by printing appropriate values
* from standard headers and by direct computation. Harder if you compute them:
* determine the ranges of various floating-point types.
*/

#include <stdio.h>
#include <float.h>
#include <limits.h>

void print_range(int min, int max, int bits, char str[])
{
    printf("%s properties:\n", str);
    printf("Min:%d\n", min);
    printf("Max:%d\n", max);
    printf("Bits:%d\n", bits);
    printf("-----------------\n");
}

void print_header()
{
    printf("%-30s|%20s|%20s|%10s|\n", " ", "Min value", "Max value", "Bits");
}

void print_row(char type[], int min, int max, int bits)
{
    printf("%-30s|%20d|%20d|%10d|\n", type, min, max, bits);
}

void print_row_with_long(char type[], long int min, long int max, int bits)
{
    printf("%-30s|%20ld|%20ld|%10ld|\n", type, min, max, bits);   
}

int main()
{
    print_header();
    print_row("char", CHAR_MIN, CHAR_MAX, CHAR_BIT);
    print_row("signed char", SCHAR_MIN, SCHAR_MAX, CHAR_BIT);
    print_row("unsigned char", 0, UCHAR_MAX, CHAR_BIT);
    print_row("signed short int", SHRT_MIN, SHRT_MAX, WORD_BIT);
    print_row("unsigned short int", 0, USHRT_MAX, WORD_BIT);
    print_row("signed int", INT_MIN, INT_MAX, WORD_BIT);
    print_row("unsigned int", 0, UINT_MAX, WORD_BIT);
    print_row_with_long("signed long int", LONG_MIN, LONG_MAX, LONG_BIT);
    print_row_with_long("unsigned long int", 0, ULLONG_MAX, LONG_BIT);
    // print_row("signed long long int", LONG_LONG_MIN, LONG_LONG_MAX, LONG_BIT);
    // print_row("unsigned long int", 0, ULONG_LONG_MAX, LONG_BIT);
    return 0;
}
