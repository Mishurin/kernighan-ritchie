/*
*  Excercise 2.4.  Write an alternate version  of squeeze(s1, s2) that
*  deletes each character in s1 that matches any character in the string s2.
*/

// Run test:
// python .\runcc.py --comp gcc --sn 2.4

#include <stdio.h>

int is_in_string(char ch, char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            return 1;
    }
    return 0;
}

void squeeze(char s1[], char s2[])
{
    int i, j;
    for (i = j = 0; s1[i] != '\0'; i++)
    {
        if(!is_in_string(s1[i], s2)) s1[j++] = s1[i];
    }
    s1[j] = '\0';
}

int main()
{
    char sample1[] = "abcdefg"; 
    squeeze(sample1, "ag");
    char sample2[] = "aaabbbccc";
    squeeze(sample2, "aacc");
    printf("%s", sample2);
    return 0;
}
