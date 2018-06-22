/*
* Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, 
* which operate on at most the first n characters of their argument strings. For example, 
* strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

// Run test
// python ./runcc.py --comp gcc --sn 5.5

#include <stdio.h>

void strn_cpy(char *, char *, int);
void strn_cat(char *, char *, int);
int strn_cmp(char *, char *, int);

int main()
{
    char lng[100];
    char shrt[3];
    strn_cpy(lng, "test_source", 4);
    printf("%s\n", lng);
    strn_cpy(shrt, "test_source", 4); // Looks like short char array will be extended dynamically
    printf("%s\n", shrt);
    strn_cpy(lng, "short", 10); // Works fine as well
    char str[] = "abc";
    strn_cat(str, "def", 3);
    printf("%s\n", str);
    strn_cat(str, "ghij", 3);
    printf("%s\n", str);
    printf("%d\n",strn_cmp("abc", "abc", 3));
    printf("%d\n",strn_cmp("abc", "abcd", 3));
    printf("%d\n",strn_cmp("abcde", "abc", 3));
    printf("%d\n",strn_cmp("abcde", "abc", 5));
    return 0;
}

void strn_cpy(char *s, char *t, int n)
{
    while (n-- && (*s++ = *t++))
        ;
    if (*t != '\0')
        *s = '\0';
}

void strn_cat(char *s, char *t, int n)
{
    while (*s != '\0')
        s++;
    while (n-- && (*s++ = *t++))
        ;
    if (*t != '\0')
        *s = '\0';
}

int strn_cmp(char *s, char *t, int n)
{
    for (; n && (*s == *t); s++, t++, --n)
        if (*s == '\0' || n == 1)
            return 0;
    return *s - *t;
}