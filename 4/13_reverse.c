/*
* Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the 
* string s in place.
*/

// Run test
// python ./runcc.py --comp gcc --sn 4.13

#include <stdio.h>
#include <string.h>

/* swap: interchange v[i] and v[j] */
void swap(char v[], int i, int j)
{
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void reverse(char s[])
{
    static int i = 0;
    int len = strlen(s);
    int j = len - i - 1;
    if (i < j)
    {
        swap(s, i++, j);
        reverse(s);
    }
}

int main()
{
    char str[] = "test";
    reverse(str);
    printf("%s\n", str);
    return 0;
}
