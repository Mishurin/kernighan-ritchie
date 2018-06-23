#include <stdio.h>
#include <ctype.h>
#include "6_utils.h"

int str_len(char *s)
{
    int cnt = 0;
    while (*s++ != '\0')
        cnt++;
    return cnt;
}

int get_line(char *s, int lim)
{
    int c, i;

    for (i = 0; --lim && (c = getchar()) != EOF && c != '\n'; s++, i++)
    {
        *s = c;
    }

    if (*s == '\n')
    {
        *s = c;
        s++;
    }

    *s = '\0';
    return i;
}

int atoi(char *s)
{
    int n = 0;
    for (; *s >= '0' && *s <= '9'; s++)
        n = 10 * n + (*s - '0');
    return n;
}

int atois(char *s)
{
    int n, sign;
    while (isspace(*s))
        s++;
    sign = (*s == '-') ? -1 : 1;
    if (*s == '+' || *s == '-')
        s++;
    for (n = 0; isdigit(*s); s++)
        n = 10 * n + (*s - '0');
    return sign * n;
}

void itoa(int n, char *s)
{
    int sign;
    long n_long = n;
    char *pts = s;

    if ((sign = n_long) < 0)
        n_long = -n_long;
    do
        *pts++ = (n_long % 10) + '0';
    while ((n_long /= 10) > 0);
    if (sign < 0)
        *pts++ = '-';
    *pts = '\0';
    reverse(s);
}

void itoar(int n, char *s)
{
    static int i = 0;

    long n_long = n;

    if (n_long / 10)
        itoar(n_long / 10, s);
    else
    {
        if (n_long < 0)
        {
            s[i++] = '-';
        }
    }
    s[i++] = (n_long < 0 ? -n_long : n_long) % 10 + '0';
    s[i] = '\0';
}

void swap(char *px, char *py)
{
    char temp;
    temp = *px;
    *px = *py;
    *py = temp;
}

void reverse(char *s)
{
    static int i = 0;
    int len = str_len(s);
    int j = len - i - 1;
    if (i < j)
    {
        swap(&s[i++], &s[j]);
        reverse(s);
    }
}

int strindex(char *s, char *t)
{
    int i, j, k;
    for (i = 0; *s != '\0'; i++)
    {
        char *pts = s;
        char * ptt = t;
        for (k = 0; *ptt != '\0' && *pts == *ptt; pts++, ptt++, k++)
            ;
        if (k > 0 && *ptt == '\0')
            return i;
        s++;
    }
    return -1;
}

#include <stdio.h>
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else if(c != EOF)
        buf[bufp++] = c;
}

int getop(char *s)
{
    static int lastc = 0;
    int c;

    if (lastc == 0)
        c = getch();
    else
    {
        c = lastc;
        lastc = 0;
    }

    while ((*s = c) == ' ' || c == '\t')
        c = getch();
    s[1] = END_OF_LINE;
    
    if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-' && c != '=')
        return c;

    if (c == '=')
    {
        *s++ = c;
        *s = END_OF_LINE;
        return ASSIGNMENT;
    }

    /* negative sign or subraction */
    if (c == '-')
    {
        lastc = getch(); // next
        if (isdigit(lastc))
        {
            *s++ = '-';
            c = *s = lastc;
            lastc = 0;
        }
        else
        {
            return '-';
        }
    }

    char signal;

    if (isalpha(c))
    {
        lastc = getch();
        *s++ = c;
        if (isspace(lastc))
        {
            signal = VARIABLE;
            *s = END_OF_LINE;
            return signal;
        } else {
            *s = lastc;
            lastc = 0;
        }

        while (isalpha(*++s = c = getch()))
            ;
        signal = COMMAND;
    }

    if (isdigit(c))
    {
        while (isdigit(*++s = c = getch()))
            ;
        if (c == '.')
            while (isdigit(*++s = c = getch()))
                ;
        signal = NUMBER;
    }

    *s = END_OF_LINE;
    if (c != EOF)
        lastc = c;
    return signal;
}