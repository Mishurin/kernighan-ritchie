/* 
* Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. 
* (Block structure will help.)
*/

// Run test
// python ./runcc.py --comp gcc --sn 4.14

#include <stdio.h>

#define swap(t, x, y) \
    {                 \
        t temp;       \
        temp = x;     \
        x = y;        \
        y = temp;     \
    }

int main()
{

    int x = 1;
    int y = 2;
    printf("%d:%d\n", x, y);
    swap(int, x, y);
    printf("%d:%d\n", x, y);

    double m = 1;
    double n = 2;
    printf("%f:%f\n", m, n);
    swap(double, m, n);
    printf("%f:%f\n", m, n);

    return 0;
}