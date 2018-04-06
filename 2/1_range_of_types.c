/*
* Exercise 2-1. Write a program to determine the ranges of char, short, int,
* and long variables, both signed and unsigned, by printing appropriate values
* from standard headers and by direct computation. Harder if you compute them:
* determine the ranges of various floating-point types.
*/

// Run test
// python .\runcc.py --comp gcc --sn 2.1

#include <stdio.h>
#include <float.h>
#include <limits.h>
#include <math.h>
// formula for float min:  b**(emin - 1)
#define FLOAT_BASE 2
#define MAX_EXPONENT 127

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
    printf("Type:%s\nMin:%e\nMax:%e\nSize:%d\n", type, min, max, bits * 8);
}

int pow_int(int base, int exp)
{
    int res = 1;
    while (exp--)
    {
        res *= base;
    }
    return res;
}

long long int pow_llong_int(int base, int exp)
{
    long long int res = 1;
    while (exp--)
    {
        res *= base;
    }
    return res;
}

float pow_float(int base, int exp)
{
    float res = 1;
    while (exp--)
    {
        res *= base;
    }
    return res;
}


unsigned long long int pow_ullong_int(int base, int exp)
{
    unsigned long long int res = 1;
    while (exp--)
    {
        res *= base;
    }
    return res;
}
 
int range_int(int max_range_val, char min_max[], int is_signed)
{
    if (is_signed)
    {
        if (min_max == "min")
        {
            return -(max_range_val / 2);
        }
        else if (min_max == "max")
        {
            return max_range_val / 2 - 1;
        }
    }
    else
    {
        if (min_max == "min")
        {
            return 0;
        }
        else if (min_max == "max")
        {
            return max_range_val - 1;
        }
    }
}

long long int range_llong_int(long long int max_range_val, char min_max[], int is_signed)
{
    if (is_signed)
    {
        if (min_max == "min")
        {
            return -(max_range_val / 2);
        }
        else if (min_max == "max")
        {
            return max_range_val / 2 - 1;
        }
    }
    else
    {
        if (min_max == "min")
        {
            return 0;
        }
        else if (min_max == "max")
        {
            return max_range_val - 1;
        }
    }
}

unsigned long long int unsigned_range_from_ullong_int(unsigned long long int max_range_val, char min_max[])
{
    if (min_max == "min")
    {
        return 0;
    }
    else if (min_max == "max")
    {
        return max_range_val - 1;
    }
}

unsigned long long int signed_range_from_ullong_int(unsigned long long int max_range_val_reduced, char min_max[])
{
    if (min_max == "min")
    {
        return -max_range_val_reduced;
    }
    else if (min_max == "max")
    {
        return max_range_val_reduced - 1;
    }
}

float min_float()
{
    int e = 8;
    int p = 24;
    int b = 2;
    int emax = 127;
    int emin = -126;
    return pow(2, emin) * (1 - pow(b, -p));
}

float max_float()
{
    int e = 8;
    int p = 24;
    int b = 2;
    int emax = 127;
    int emin = -126;
    // (1 - b**-p) * b**emax
    return pow(b, pow(2, e-1)) * (1 - pow(b, -p));
}

int main()
{
    print_header();
    print_row("char", CHAR_MIN, CHAR_MAX, CHAR_BIT);
    print_row("signed char", SCHAR_MIN, SCHAR_MAX, CHAR_BIT);
    print_row("unsigned char", 0, UCHAR_MAX, CHAR_BIT);

    print_row("signed short int", SHRT_MIN, SHRT_MAX, sizeof(short int) * 8);
    print_row("unsigned short int", 0, USHRT_MAX, sizeof(unsigned short int) * 8);

    print_row("signed int", INT_MIN, INT_MAX, WORD_BIT);
    print_row_with_ui("unsigned int", 0, UINT_MAX, WORD_BIT);

    print_row_with_long("signed long int", LONG_MIN, LONG_MAX, LONG_BIT);
    print_row_with_ulong("unsigned long int", 0, ULONG_MAX, LONG_BIT);

    print_row_with_llong("signed long long int", LLONG_MIN, LLONG_MAX, LONG_BIT);
    print_row_with_ullong("unsigned long long int", 0, ULLONG_MAX, LONG_BIT);

    printf("****************************\n");

    print_row_with_float("float", FLT_MIN, FLT_MAX, sizeof(float));

    printf("****************************\n");

    print_header();
    int char_size = sizeof(char) * 8;
    int max_char_range = pow_int(2, char_size);
    print_row("char", range_int(max_char_range, "min", 1), range_int(max_char_range, "max", 1), char_size);
    print_row("signed char", range_int(max_char_range, "min", 1), range_int(max_char_range, "max", 1), char_size);
    print_row("unsigned char", range_int(max_char_range, "min", 0), range_int(max_char_range, "max", 0), char_size);
    int short_int_size = sizeof(short int) * 8;
    int max_short_int_range = pow_int(2, short_int_size);
    print_row("signed short int", range_int(max_short_int_range, "min", 1), range_int(max_short_int_range, "max", 1), short_int_size);
    print_row("unsigned short int", range_int(max_short_int_range, "min", 0), range_int(max_short_int_range, "max", 0), short_int_size);
    int int_size = sizeof(int) * 8;
    long long int max_int_range = pow_llong_int(2, int_size);
    print_row("signed int", range_llong_int(max_int_range, "min", 1), range_llong_int(max_int_range, "max", 1), int_size);
    print_row_with_ui("unsigned int", range_llong_int(max_int_range, "min", 0), range_llong_int(max_int_range, "max", 0), int_size);

    int long_int_size = sizeof(long int) * 8;
    unsigned long long int reduced_long_int_range = pow_ullong_int(2, long_int_size - 1); // Oferflow circumvent
    unsigned long long int max_long_int_range = pow_ullong_int(2, long_int_size);
    print_row_with_long("signed long int", signed_range_from_ullong_int(reduced_long_int_range, "min"), signed_range_from_ullong_int(reduced_long_int_range, "max"), long_int_size);
    print_row_with_ulong("unsigned long int", unsigned_range_from_ullong_int(max_long_int_range, "min"), unsigned_range_from_ullong_int(max_long_int_range, "max"), long_int_size);

    int llong_int_size = sizeof(long long int) * 8;
    unsigned long long int reduced_llong_int_range = pow_ullong_int(2, llong_int_size - 1); // Oferflow circumvent
    unsigned long long int max_llong_int_range = pow_ullong_int(2, llong_int_size);
    print_row_with_long("signed long int", signed_range_from_ullong_int(reduced_llong_int_range, "min"), signed_range_from_ullong_int(reduced_llong_int_range, "max"), llong_int_size);
    print_row_with_ulong("unsigned long int", unsigned_range_from_ullong_int(max_llong_int_range, "min"), unsigned_range_from_ullong_int(max_llong_int_range, "max"), llong_int_size);
    
    printf("****************************\n");
    print_row_with_float("float", min_float(),  max_float(), sizeof(float));

    return 0;
}
