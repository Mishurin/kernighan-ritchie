/*
* Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, 
* convert an integer into a string by calling a recursive routine.
*/

// Run test
// python ./runcc.py --comp gcc --sn 4.12

#include <stdio.h>

void itoa(int n, char s[])
{
    static int i = 0;

    long n_long = n;

    if (n_long / 10)
        itoa(n_long / 10, s);
    else
    {
        i = 0;
        if (n_long < 0)
        {
            s[i++] = '-';
        }
    }
    s[i++] = (n_long < 0? -n_long: n_long) % 10 + '0';
    s[i] = '\0';
}

int main()
{
    char str[1000];
    int a = -2147483648; // Smallest negative integer
    itoa(a, str);
    printf("%s\n", str);
    itoa(100, str);
    printf("%s\n", str);
    return 0;
}