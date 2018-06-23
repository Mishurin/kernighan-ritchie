/*
* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with 
* pointers instead of array indexing. Good possibilities include getline (Chapters 1
* and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), 
* and strindex and getop (Chapter 4).
*/

// Run test:
// python ./runcc.py --comp gcc --i ./5/utils/ --inc ./utils/6_utils.c --sn 5.6_2 --opts < ./5/mocks/6_2_utils

#include <stdio.h>
#include "6_utils.h"

int main()
{
    char str[100];
    int len;
    len = get_line(str, 100);
    printf("String length: %d, String check: %d, String: %s\n", len, str_len(str), str);
    len = get_line(str, 100);
    printf("String length: %d, String check: %d, String: %s\n", len, str_len(str), str);
    return 0;
}