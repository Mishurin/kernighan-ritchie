/*
* Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in 
* the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of 
* either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. 
* Arrange that a leading or trailing - is taken literally.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_LENGTH 1000

void expand(char s1[], char s2[])
{
    int len = strlen(s1);
    char ch;
    int target_counter = 0;
    char range_start;
    char range_started = 0;
    char is_range = 0;
    for (int i = 0; i < len; i++)
    {
        ch = s1[i];
        if ((i == 0 || i == (len - 1)) && ch == '-')
        {
            s2[target_counter++] = ch;
        }
        else if (range_started && ch == '-')
        {
            is_range = 1;
        }

        if (isalnum(ch))
        {
            if (!range_started && !is_range)
            {
                range_start = ch;
                range_started = 1;
            }
            else if (is_range)
            {
                int start = (int)range_start;
                int end = (int)ch;
                //printf("%d:%d", start, end);
                for (int j = start; j <= end; j++)
                {
                    s2[target_counter++] = (char)j;
                }
                is_range = 0;
                range_started = 0;
            }
        }
    }

    s2[target_counter] = '\0';
}

int main()
{
    char expanded[MAX_STRING_LENGTH];

    expand("a-d", expanded);
    printf("%s\n", expanded);
    expand("a-z0-9", expanded);
    printf("%s\n", expanded);
    expand("a-b-c", expanded);
    printf("%s\n", expanded);
    expand("-a-z", expanded);
    printf("%s\n", expanded);
    expand("-a-z-", expanded);
    printf("%s\n", expanded);
    return 0;
}