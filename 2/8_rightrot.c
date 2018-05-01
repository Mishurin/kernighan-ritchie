/*
 * Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer x 
 * rotated to the right by n positions.
*/

#include <stdio.h>

// Run test:
// python ./runcc.py --comp gcc --sn 2.8

unsigned int UNSIGNED_INT_ZERO = 0;
unsigned int x = 5;
unsigned int y = 10;
int n = 4;

unsigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}

unsigned int mask(int p, int n)
{
    unsigned int mask_base;
    if(sizeof(UNSIGNED_INT_ZERO) * 8 == n) {
        mask_base = ~UNSIGNED_INT_ZERO;
    } else {
        mask_base = ~(~0 << n);
    }
    return mask_base << (p - n + 1);
}

unsigned int setbits(unsigned x, int p, int n, unsigned y)
{
    unsigned int mask_in_position = mask(p, n);
    return (x & ~mask_in_position) | ((y << p - n + 1) & mask_in_position);
    
}

unsigned int reversebits(unsigned int x, int n)
{
    
    unsigned int res = ~(~UNSIGNED_INT_ZERO << n);
    for (int i = 0, j = n - 1; i < n; i++, j--)
    {
        res = setbits(res, j, 1, getbits(x, i, 1));
    }
    return res;
}

unsigned int rightrot(unsigned x, int n)
{
    // 0000000000000000000000000000<0101>: 5 -> 
    // <0101>0000000000000000000000000000: 1342177280
    
    // 0000000000000000000000000000<1010>: 10 -> 
    // <1010>0000000000000000000000000000: 2684354560
    
    unsigned int res;
    int bits = sizeof(x) * 8;
    return setbits(x >> n, bits - 1, n, x);
    
}

int main()
{
    printf("Rotated x: %u\n", rightrot(x, n)); // => 1342177280
    printf("Rotated y: %u\n", rightrot(y, n)); // => 2684354560
    return 0;
}