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
#define DASH_SYMBOL '-'
#define END_OF_STRING '\0'

void expand(char s1[], char s2[])
{
    int start, end;
    int is_range = 0, range_end = 0, range_started = 0, target_index = 0, len = strlen(s1);
    char ch;

    for (int i = 0; i < len; i++)
    {
        ch = s1[i];
        if ((i == 0 || i == (len - 1)) && ch == DASH_SYMBOL)
        {
            s2[target_index++] = ch;
        }
        else if (range_started && ch == DASH_SYMBOL)
        {
            is_range = 1;
        }

        if (isalnum(ch))
        {
            if (!range_started && !is_range)
            {
                range_started = 1;
                start = (int)ch;
            }
            else if (is_range)
            {
                if(s1[i + 1] == DASH_SYMBOL && isalnum(s1[i + 2]))
                {
                    continue;
                }
                end = (int)ch;
                for (int j = start; j <= end; j++)
                {
                    s2[target_index++] = (char)j;
                }
                is_range = 0;
                range_started = 0;
            }
        }
    }

    s2[target_index] = END_OF_STRING;
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
    expand("-0-3-5", expanded);
    printf("%s\n", expanded);
    return 0;
}