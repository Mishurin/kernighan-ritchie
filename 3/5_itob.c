/*
* Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b 
* character representation in the string s. In particular, itob(n,s,16) formats s as a 
* hexadecimal integer in s.
*/

#include <stdio.h>
#include <string.h>

#define MARKER_START '<'
#define MARKER_END '>'
#define MAX_STRING_LENGTH 1000

// Run test
// python ./runcc.py --comp gcc --sn 3.5

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void itob(int n, char s[], int b)
{
    int i = 0;
    do
    {
        s[i++] = MARKER_END;
        s[i++] = (n % b) + '0';
        s[i++] = MARKER_START;
        n /= b;
    } while (n != 0);
    s[i] = '\0';
    reverse(s);
}

int main()
{

    char target[MAX_STRING_LENGTH];
    itob(103, target, 2); // 1100111
    printf("b=2:%s\n", target);
    itob(0, target, 2); // 0
    printf("b=2:%s\n", target);
    itob(103, target, 8); // 147
    printf("b=8:%s\n", target);
    itob(103, target, 16); // 67
    printf("b=16:%s\n", target);
    return 0;
}