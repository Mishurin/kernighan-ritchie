
/*
* Exercise 4-1. Write the function strindex(s,t) which returns the position of the 
* rightmost occurrence of t in s, or -1 if there is none.
*/

// Run test
// python ./runcc.py --comp gcc --sn 4.1

#include <stdio.h>

int strindex(char s[], char t[])
{
    int i, j, k, last_index = -1;
    for (i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
            last_index = i;
    }
    return last_index;
}

int main()
{
    printf("Index:%d\n", strindex("test test test", "test")); // 10
    printf("Index:%d\n", strindex("test test test", "test ")); // 5
    printf("Index:%d\n", strindex("test test test", "test1")); // -1
    return 0;
}
