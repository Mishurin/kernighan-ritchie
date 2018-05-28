/*
* Exercise 3-6. Write a version of itoa that accepts three arguments instead of two. The 
* third argument is a minimum field width; the converted number must be padded with blanks 
* on the left if necessary to make it wide enough.
*/

#include <string.h>
#include <stdio.h>

#define PADDING_CHAR '.'
#define MAX_STRING_LENGTH 1000

// Run test
// python ./runcc.py --comp gcc --sn 3.6

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itoa(int n, char s[], int min_width)
{
    int i, sign;
    long n_long = n;
    if ((sign = n_long) < 0)
    {
        n_long = n;
        n_long = -n_long;
    }
    i = 0;
    do
    {
        s[i++] = n_long % 10 + '0';
        min_width--;
    } while ((n_long /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    while (min_width > 0)
    {
        s[i++] = PADDING_CHAR;
        min_width--;
    }
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char target[MAX_STRING_LENGTH];
    itoa(-2147483648, target, 5);
    printf("%s\n", target);
    itoa(100, target, 11);
    printf("%s\n", target);
    itoa(-20, target, 10);
    printf("%s\n", target);
    return 0;
}