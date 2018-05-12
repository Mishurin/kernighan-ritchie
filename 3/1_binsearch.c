/*
* Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice 
* (at the price of more tests outside.) Write a version with only one test inside the loop
* and measure the difference in run-time.
*/

#include <stdio.h>

int binsearch(int x, int v[], int n)
{
    int low, high, mid = 0;
    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid])
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    if (v[mid] == x)
        return mid;
    else
        return -1;
}

int main()
{
    int x = 5;
    int v[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = 10;
    printf("Index: %d\n", binsearch(x, v, n));
    return 0;
}
