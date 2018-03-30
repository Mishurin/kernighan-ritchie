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

void print_row_with_ui(char type[], long int min, long int max, int bits)
{
    printf("%-30s|%20u|%20u|%10d|\n", type, min, max, bits);  
}

void print_row_with_long(char type[], long int min, long int max, int bits)
{
    printf("%-30s|%20ld|%20ld|%10d|\n", type, min, max, bits);  
}

void print_row_with_ulong(char type[], unsigned long int min, unsigned long int max, int bits)
{
    printf("%-30s|%20lu|%20lu|%10d|\n", type, min, max, bits);   
}

void print_row_with_llong(char type[], long long int min, long long int max, int bits)
{
    printf("%-30s|%20lld|%20lld|%10d|\n", type, min, max, bits);   
}

void print_row_with_ullong(char type[], unsigned long long int min, unsigned long long int max, int bits)
{
    printf("%-30s|%20llu|%20llu|%10d|\n", type, min, max, bits);   
}

void print_row_with_float(char type[], float min, float max, int bits)
{
    printf("Type:%s\nMin:%f\nMax:%f\nSize:%d\n", type, min, max, bits * 8);   
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
    print_row_with_ui("unsigned int", 0, UINT_MAX, WORD_BIT);
    print_row_with_long("signed long int", LONG_MIN, LONG_MAX, LONG_BIT);
    print_row_with_ulong("unsigned long int", 0, ULONG_MAX, LONG_BIT);
    print_row_with_llong("signed long long int", LLONG_MIN, LLONG_MAX, LONG_BIT);
    print_row_with_ullong("unsigned long long int", 0, ULLONG_MAX, LONG_BIT);
    printf("****************************\n");
    print_row_with_float("float", FLT_MIN, FLT_MAX, sizeof(float));
    return 0;
}
