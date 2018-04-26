/*
* Exercise 2.6. Write a function setbits(x, p, n, y) that returns x with the n
* bits that begin at position p set to the rightmost n bits of y, leaving other
* bits unchanged.
*/

#include <stdio.h>

// Run test
// python .\runcc.py --comp gcc --sn 2.6

unsigned int UNSIGNED_INT_ZERO = 0;
unsigned int x = 5;
unsigned int y = 10;
int n = 3;
int p = 4;
/*
* Assume we have 8-bit numbers
* x = 5: [0|0|0|0|0|1|0|1] => 101
* y = 10: [0|0|0|0|1|0|1|0] => 1010
* n = 3
* p = 4 (p = 0,1,...,integer bit-size), count starts to the right
*/
unsigned int create_mask_in_position(int p, int n)
{
    /*
    * We need to replace n-places with onses starting from
    * [0|0|0|0|0|1|0|1] -> [0|0|0<1|1|1>0|0]
    * This will give an opportunity to make 'holes' or put number of zeros (n)
    * in certain pozition (n) i.e. in this case [1|1|1<0|0|0>1|1] = ~maskInPosition(x)
    * [0|0|0|0|0|0|0|0]:0 = zero(8-bit zero)
    * [1|1|1|1|1|1|1|1]:~0 = ones (zero in reverse)
    * <1|1|1|1|1|1>0|0]: ones << p - n + 1  = mr (margin right)
    * <1|1|1>0|0|0|0|0]: ones << p + 1  = ml (margin left)
    * [0|0|0<1|1|1>0|0]: mr ^ ml = peak => 28
    */
    unsigned int ones, margin_right, margin_left, peak;

    ones = ~UNSIGNED_INT_ZERO;
    margin_right = ones << p - n + 1;
    margin_left = ones << p + 1;
    peak = margin_right ^ margin_left;
    return peak;
}

unsigned int clear_boundaries(unsigned int y, int n)
{
    /*
    * Before shifting bits into a position of replacement let's clear all bits but
    * target ones
    * [0|0|0|0|1<0|1|0> -> [0|0|0|0|0<0|1|0>
    * Lets create a mask of ones:
    * [0|0|0|0|0|0|0|0]:0 = zero(8-bit zero)
    * [1|1|1|1|1|1|1|1]:~0 = ones (zero in reverse)
    * [1|1|1|1|1<0|0|0>: y << n = right_margin
    * [0|0|0|0|0<1|1|1>: ~right_margin = left_padding
    * [0|0|0|0|0<0|1|0>: y & left_padding => 2
    */
    unsigned int ones, right_margin, left_pading;
    ones = ~UNSIGNED_INT_ZERO;
    right_margin = ones << n;
    left_pading = ~right_margin;
    return y & left_pading;
}

unsigned int align_bits_to_position(unsigned int bits, int p, int n)
{
    /*
    *  We need to shift/align target n-bits to the position of replacement
    * [0|0|0|0|0<0|1|0> -> [0|0|0<0|1|0>0|0]
    * [0|0|0<0|1|0>0|0]: bits << p - n + 1 => 8
    */
    return bits << p - n + 1;
}

unsigned int create_gap_in_position(unsigned int x, int p, int n)
{
    /* 
    * We need create a gap/hole on the position of replacement of size of
    * replacement:
    * [0|0|0<0|0|1>0|1] -> [0|0|0<0|0|0>0|1]
    * Lets create a hole-mask a required place:
    * [1|1|1<0|0|0>1|1]: ~create_mask_in_position(p, n) = mask
    * [0|0|0<0|0|0>0|1]: x & mask = 1
    */
   return x & ~create_mask_in_position(p, n);
}

unsigned int setbits(unsigned int x, int p, int n, unsigned int y)
{
    /* 
    * Lets superpose target bits and replacement bits:
    * [0|0|0<0|0|0>0|1]: create_gap_in_position(x, p, n) = target;
    * [0|0|0<0|1|0>0|0]: align_bits_to_position(clear_boundaries(y, n), p, n) = replacement;
    * [0|0|0<0|1|0>0|1]: target | replacement => 9
    */
    return create_gap_in_position(x, p, n) | align_bits_to_position(clear_boundaries(y, n), p, n);
}

int main()
{
    printf("Mask in position: %u\n", create_mask_in_position(p, n));                                   // => 28
    printf("Cleared boundaries: %u\n", clear_boundaries(y, n));                                        // => 2
    printf("Poristioned for replacement: %u\n", align_bits_to_position(clear_boundaries(y, n), p, n)); // => 8
    printf("Target with gap: %u\n", create_gap_in_position(x, p, n)); // => 1
    printf("With bits set: %u\n", setbits(x, p, n, y)); // => 9
    return 0;
}