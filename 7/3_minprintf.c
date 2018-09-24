/*
* Exercise 7-3. Revise minprintf to handle more of the other facilities of printf.
*/

// Run test:
// python ./runcc.py -w --comp gcc --sn 7.3

#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>
#define MAX_TOKEN_LENGTH 100
#define EOS '\0'

int main(int argc, char const *argv[])
{
    void minprintf(char *fmt, ...);

    // Some tests
    minprintf("%s\n", "test");
    minprintf(":%-15.10s:\n", "hello, world");
    minprintf("%s:%.5f:\n", "Real number", 1.234);
    minprintf("%%%s\n", "test");
    char test[10];
    char *testpt = test;
    minprintf("%p\n", *testpt);
    return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    void *ptval;
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        char token[MAX_TOKEN_LENGTH];
        char *tpt = token;
        *tpt++ = '%';
        while (*++p != 'd' && *p != 'i' && *p != 'o' && *p != 'x' && *p != 'X' 
            && *p != 'c' && *p != 'f' && *p != 'e' && *p != 'E' && *p != 'g' 
            && *p != 'G' && *p != 's' && *p != 'p' && *p != '%' && *p != EOS)
        {
            if (*p != '.' && *p != '-' && !isdigit(*p))
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
        case 'X':
        case 'c':
            ival = va_arg(ap, int);
            *tpt = EOS;
            printf(token, ival);
            break;
        case 'f':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
            dval = va_arg(ap, double);
            *tpt = EOS;
            printf(token, dval);
            break;
        case 's':
            sval = va_arg(ap, char *);
            *tpt = EOS;
            printf(token, sval);
            break;
        case 'p':
            sval = va_arg(ap, void *);
            *tpt = EOS;
            printf(token, ptval);
            break;
        case '%':
            p--;
            printf("%c", '%');
            break;
        default:
            *tpt = EOS;
            printf("%s", token);
            break;
        }
    }
    va_end(ap); /* clean up when done */
}