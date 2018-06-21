/*
* Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at 
* the end of the string s, and zero otherwise.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 5.4

#include <stdio.h>
#include <string.h>

int strend(char *, char *);

int main()
{
    char s[] = "my test";
    char t[] = "test";

    printf("Result: %d\n", strend(s, t));
    printf("Result: %d\n", strend(s, "test1"));
    printf("Result: %d\n", strend(s, "test "));
    printf("Result: %d\n", strend("test", "my test"));
    printf("Result: %d\n", strend("my test", "my test"));
    return 0;
}

int strend(char *s, char *t)
{
    int slen = strlen(s);
    int tlen = strlen(t);
    if (slen < tlen)
        return 0;
    while (--slen >= 0 && --tlen >= 0)
    {
        if (s[slen] != t[tlen])
            return 0;
    }
    return 1;
}
