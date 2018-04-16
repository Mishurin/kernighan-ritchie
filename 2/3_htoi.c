/*
* Exercise 2.3. Write a function htoi(s) which converts a string of hexadecimal
* digits (including an optional 0x or 0X) into its equivalent integer value. The
* allowable digits are 0 through 9, a through f, and A through F
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

enum hexints
{
    A = 10,
    B,
    C,
    D,
    E,
    F
};
enum hexchars
{
    a = 'a',
    b = 'b',
    c = 'c',
    d = 'd',
    e = 'e',
    f = 'f'
};

int char_to_int(char ch)
{
    if (ch == a)
    {
        return A;
    }
    else if (ch == b)
    {
        return B;
    }
    else if (ch == c)
    {
        return C;
    }
    else if (ch == d)
    {
        return D;
    }
    else if (ch == e)
    {
        return E;
    }
    else if (ch == f)
    {
        return F;
    }
    else
    {
        return -1;
    }
}

int htoi(char string[])
{
    int len = strlen(string);
    int i = 0;
    int hex_reg = len - 1;
    char current_char;
    int converted_digit;
    int res = 0;
    if (len > 2 && string[0] == '0' && tolower(string[1]) == 'x')
    {
        i = i + 2;
        hex_reg = hex_reg - 2;
    }

    for (i; i < len; i++)
    {
        current_char = string[i];
        if (isdigit(current_char))
        {
            converted_digit = current_char - '0';
        }
        else if (isalpha(current_char))
        {
            converted_digit = char_to_int(tolower(current_char));
        }
        else
        {
            return -1;
        }

        res += converted_digit * pow(16, hex_reg);
        hex_reg--;
    }

    return res;
}

int main()
{
    printf("%d\n", htoi("1"));
    printf("%d\n", htoi("F"));
    printf("%d\n", htoi("1F"));
    printf("%d\n", htoi("0x1F"));
    printf("%d\n", htoi("0X1F"));
    printf("%d\n", htoi("3A5"));
    printf("%d\n", htoi("0x3A5"));
    printf("%d\n", htoi("0X3A5"));
    printf("%d\n", htoi("3A53AF"));
    // Exceptional cases:
    printf("%d\n", htoi("3A5@3AF"));
    printf("%d\n", htoi("@"));
    printf("%d\n", htoi("0x"));
    printf("%d\n", htoi("0X"));
}