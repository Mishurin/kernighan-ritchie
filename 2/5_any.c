/*
*   Exercise 2.5. Write the function any(s1, s2), which returns the first
*   location in the string s1 where any character from the string s2 occurs,
*   or -1 if s1 contains no characters from s2. (The standard library function)
*   strpbrk does the same job but returns a poinger to the location.)
*/

#include <stdio.h>
#define NOT_FOUND -1

// Run test
// python .\runcc.py --comp gcc --sn 2.5

int is_in_string(char ch, char str[])
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            return 1;
    }
    return 0;
}

int any(char s1[], char s2[])
{
    for (int i = 0; s1[i] != '\0'; i++)
    {
        if(is_in_string(s1[i], s2))
        {
            return i;
        }
    }
    return NOT_FOUND;
}

int main()
{
    printf("%d\n", any("abc", "a"));
    printf("%d\n", any("abc", "b"));
    printf("%d\n", any("abc", "c"));
    printf("%d\n", any("abc", "dec"));
    printf("%d\n", any("abc", "def"));
    return 0;
}