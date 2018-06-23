
/*
* Exercise 5-6. Rewrite appropriate programs from earlier chapters and exercises with 
* pointers instead of array indexing. Good possibilities include getline (Chapters 1
* and 4), atoi, itoa, and their variants (Chapters 2, 3, and 4), reverse (Chapter 3), 
* and strindex and getop (Chapter 4).
*/

// python ./runcc.py --comp gcc --i ./5/utils/ --inc ./utils/6_utils.c --sn 5.6_7 --opts < ./5/mocks/6_7_getop

#include <stdio.h>
#include "6_utils.h"

int main()
{
    char s[1000];
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    printf("Type: %c, Content: %s\n", getop(s), s);
    return 0;
}