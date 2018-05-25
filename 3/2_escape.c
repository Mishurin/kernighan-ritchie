/*
 * Exercise 3-2. Write a function escape(s,t) that converts characters like newline and 
 * tab into visible escape sequences like \n and \t as it copies the string t to s. Use 
 * a switch. Write a function for the other direction as well, converting escape sequences 
 * into the real characters.
*/

#include <stdio.h>
#include <string.h>

#define MAX_STR_LENGTH 1000

// Run test
// python ./runcc.py --comp gcc --sn 3.2 --opts < ./3/mocks/2_escape.txt

void escape(char s[], char t[])
{
    int len = strlen(t);
    int j = 0;
    for (int i = 0; i < len; i++, j++)
    {
        char ch = t[i];
        switch (ch)
        {
        case '\n':
            s[j++] = '\\';
            s[j] = 'n';
            break;
        case '\r':
            s[j++] = '\\';
            s[j] = 'r';
            break;
        case '\t':
            s[j++] = '\\';
            s[j] = 't';
            break;
        default:
            s[j] = ch;
        }
    }
    s[++j] = '\0';
}

void unescape(char s[], char t[])
{
    int len = strlen(t);
    int j = 0;

    for (int i = 0; i < len; i++)
    {
        char ch = t[i];
        char next_ch = t[i + 1];
        char insert_ch;

        if (ch == '\\')
        {
            switch (next_ch)
            {
            case 'n':
                insert_ch = '\n';
                i++;
                break;
            case 'r':
                insert_ch = '\r';
                i++;
                break;
            case 't':
                insert_ch = '\t';
                i++;
                break;
            default:
                insert_ch = ch;
                break;
            }
        }
        else
        {
            insert_ch = ch;
        }

        s[j++] = insert_ch;
    }
    s[j] = '\0';
}

int main()
{
    char c;
    int count = 0;
    char s[MAX_STR_LENGTH]; // Target
    char t[MAX_STR_LENGTH]; // Source

    while ((c = getchar()) != EOF)
    {
        t[count] = c;
        count++;
    }

    t[count] = '\0';

    printf("%s\n", t);

    escape(s, t);
    printf("%s\n", s);

    unescape(t, s);

    printf("%s\n", t);

    return 0;
}