/*
 * Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 
 * 1-bit in x.
 * Explain why. Use this observation to write a faster version of bitcount.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 2.9

#include <stdio.h>

int convert(int a)
{
    if (a < 0)
        a = ~(-a) + 1;
    return a;
}

int bitcount(unsigned int x)
{
    int count;
    for (count = 0; x != 0; x &= x - 1)
    {
        count++;
    }
    return count;
}

int main()
{
    printf("Count:%d\n", convert(-1));
    printf("Count:%d\n", bitcount(0));
    printf("Count:%d\n", bitcount(5));
    printf("Count:%d\n", bitcount(255));
    return 0;
}