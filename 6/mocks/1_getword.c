#if X == 1 // if could be recognized as keyword
#define A X
#endif

#include <stdio.h>

int _int_var = 1;

int main()
{
    /* Comment that contain keyword 'int'
    * 
    */
    char * ps = "float"; // pointer to string called 'float'
    return 0;
}