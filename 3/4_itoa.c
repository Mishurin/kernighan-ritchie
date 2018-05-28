/*
* Exercise 3-4. In a two's complement number representation, our version of itoa does not 
* handle the largest negative number, that is, the value of n equal to -(2 wordsize-1 ). 
* Explain why not. Modify it to print that value correctly, regardless of the machine on 
* which it runs.
*/

#include <string.h>
#include <stdio.h>

// Run test
// python ./runcc.py --comp gcc --sn 3.4

/* reverse: reverse string s in place */
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

void itoa(int n, char s[])
{
    int i, sign;
    /* To avoid overflow during conversion to a positive integer we introduce
    * longer intermediate variable which is capable to store 2147483648 which is larger
    * than max allowed integer.
    */
    long n_long;
    if ((sign = n) < 0)
    {
        n_long = n;
        n_long = -n_long;
    }
    i = 0;
    do
    {
        s[i++] = n_long % 10 + '0';
    } while ((n_long /= 10) > 0);
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

int main()
{
    char str[1000];
    int a = -2147483648; // Smallest negative integer
    itoa(a, str);
    printf("%s\n", str);
    return 0;
}