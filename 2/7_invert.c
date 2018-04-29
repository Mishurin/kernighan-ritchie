/*
* Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at position p
* inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/

// Run test:
// python ./runcc.py --comp gcc -- sn 2.7

#include <stdio.h>

unsigned int UNSIGNED_INT_ZERO = 0;
unsigned int x = 5; // 00000101
int p = 4; 
int n = 3;


unsigned int create_maske_in_position(int p, int n)
{
    return (~(~UNSIGNED_INT_ZERO << n)) << (p - n + 1);
}

unsigned int invert(unsigned int x, int p, int n)
{
    int mask = create_maske_in_position(p, n);
    return (x & ~mask) | (~x & mask);
}

/*
765<432>10
000<001>01 -> 5
000<110>01 -> 25
*/

int main()
{
    printf("Inverted bits:%d\n", invert(x, p, n)); // => 25
    return 0;
}
