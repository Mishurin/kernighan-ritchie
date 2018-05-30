/*
*   Exercise 4-2. Extend atof to handle scientific notation of the form
* 123.45e-6
* where a floating-point number may be followed by e or E and an optionally signed exponent.
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Run test
// python ./runcc.py --comp gcc --sn 4.2

double atof(char s[])
{
    double val, power;
    int i, sign;
    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;
    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');
    if (s[i] == '.')
        i++;
    for (power = 1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10;
    }

    if (tolower(s[i]) == 'e')
    {
        int exp_sign, exp_val;

        i++;

        exp_sign = (s[i] == '-') ? -1 : 1;

        if (s[i] == '+' || s[i] == '-')
            i++;

        for (exp_val = 0; isdigit(s[i]); i++)
        {
            exp_val = 10 * exp_val + (s[i] - '0');
        }

        for (int j = 0; j < exp_val; j++)
        {
            if (exp_sign == 1)
            {
                power /= 10;
            }
            else
            {
                power *= 10;
            }
        }
    }

    return sign * val / power;
}

int main()
{

    printf("%.2f\n", atof("123.45e+2"));  // 12345.0
    printf("%.2f\n", atof("123.45e2"));   // 12345.0
    printf("%.8f\n", atof("123.45e-6"));  // 0.00012345
    printf("%.8f\n", atof("123.45E-6"));  // 0.00012345
    printf("%.8f\n", atof("-123.45E-6")); // -0.00012345

    return 0;
}