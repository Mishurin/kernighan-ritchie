/*
* Exercise 7-4. Write a private version of scanf analogous to minprintf from the 
* previous section.
*/

// Run test:
// python ./runcc.py -w --comp gcc --sn 7.4 --opts < ./7/mocks/4_scanf.txt

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_TOKEN_LENGTH 100
#define EOS '\0'

int main(int argc, char const *argv[])
{
    int minscanf(char *fmt, ...);
    int day, year;
    char monthname[20];
    printf("Items found:%d\n", minscanf("%d %s %d", &day, monthname, &year));
    printf("Check:%d %s %d\n", day, monthname, year);
    return 0;
}

int minscanf(char *fmt, ...)
{
    va_list ap;
    char *p, *tstartp, *tpt, *sval, token[MAX_TOKEN_LENGTH];
    int *ival, has_prefix = 0, tokens_found;
    double *dval;
    
    tstartp = token;

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        if (!has_prefix)
            tpt = tstartp;
        if (*p != '%')
        {

            *tpt++ = *p;
            has_prefix = 1;
            continue;
        }

        has_prefix = 0;

        *tpt++ = '%';

        while (*++p != 'd' && *p != 'i' && *p != 'o' && *p != 'x' && *p != 'c' 
            && *p != 's' && *p != 'e' && *p != 'f' && *p != 'g' && *p != '%' 
            && *p != EOS)
        {
            if (*p != '*' && *p != 'h' && *p != 'l' && *p != 'L' && !isdigit(*p))
                break;
            *tpt++ = *p;
        }

        *tpt++ = *p;

        switch (*p)
        {
        case 'd':
        case 'i':
        case 'o':
        case 'x':
        case 'c':
            ival = va_arg(ap, int *);
            *tpt = EOS;
            tokens_found += scanf(token, ival);
            break;
        case 's':
            sval = va_arg(ap, char *);
            *tpt = EOS;
            tokens_found += scanf(token, sval);
            break;
        case 'e':
        case 'f':
        case 'g':
            dval = va_arg(ap, double *);
            *tpt = EOS;
            tokens_found += scanf(token, dval);
            printf("%d\n", tokens_found);
            break;
        case '%':
            sval = va_arg(ap, char *);
            p--;
            *--tpt = EOS;
            tokens_found += scanf(token, sval);
            break;
        default:
            sval = va_arg(ap, char *);
            *tpt = EOS;
            tokens_found += scanf(token, sval);
            break;
        }
    }

    va_end(ap);
    return tokens_found;
}
