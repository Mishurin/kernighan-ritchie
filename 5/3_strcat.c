/*
* Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2: 
* strcat(s,t) copies the string t to the end of s.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 5.3

#include <stdio.h>

void str_cat(char *s, char *t);
int main()
{
    char str[] = "abc";
    char appendix[] = "def";
    str_cat(str, appendix);
    printf("Result:%s\n", str);
    return 0;
}

/* strcat: concatenate t to end of s; s must be big enough */
void str_cat(char *s, char *t)
{
    int i, j;
    i = j = 0;
    while (*s != '\0') /* find end of s */
        s++;
    while (*s++ = *t++) /* copy t */
        ;
}