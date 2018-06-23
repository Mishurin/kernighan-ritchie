/*
* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with 
* pointers instead of array indexing. Good possibilities include getline (Chapters 1
* and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), 
* and strindex and getop (Chapter 4).
*/

// Run test:
// python ./runcc.py --comp gcc --i ./5/utils/ --inc ./utils/6_utils.c --sn 5.6_6

#include <stdio.h>
#include "6_utils.h"

int main()
{
    printf("Result %d\n", strindex("test", "st"));
    printf("Result %d\n", strindex("test", "st1"));
    return 0;
}