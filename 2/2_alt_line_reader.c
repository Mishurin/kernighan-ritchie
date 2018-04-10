/*
* Exercise 2.2. Write a loop equivalent to the loop above without using && or ||.
*/

// Run test:
// python .\runcc.py --comp gcc --sn 2.2 --opts "<" .\2\mocks\text_sample.txt

#include <stdio.h>

#define MAX_LINE_LENGTH 1000

int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1; i++)
    {
        if((c = getchar()) == EOF)
        {
            break;
        } 
        if(c == '\n')
        {
           break;
        }
        s[i] = c;
    }
    
    if( c == '\n')
    {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

int main()
{
    char line[MAX_LINE_LENGTH];
    int length;
    while((length = get_line(line, MAX_LINE_LENGTH)) > 0) 
    {
        printf("Line:%sLength:%d\n", line, length);
    }
    return 0;
}
