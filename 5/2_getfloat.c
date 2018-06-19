/* 
* Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does 
* getfloat return as its function value?
*/

// Run test
// python ./runcc.py --comp gcc --sn 5.2 --opts  < ./5/mocks/2_getfloat | head

#include <stdio.h>
#include <ctype.h>
#define SIZE 1000

int n, getfloat(float *);
float array[SIZE];

int main()
{
    for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
        ;
    for (int i = 0; i < SIZE; i++)
    {
        printf("%f\n", array[i]);
    }
    return 0;
}

int getch(void);
void ungetch(int);

/* getfloat: get next float from input into *pn */
// Returning type doesn't matter since EOF only is important
int getfloat(float *pn)
{
    int c, sign;

    do
    {
        c = getch();
    } while (!isdigit(c) && c != '-' && c != '+' && c != EOF); // skip garbage

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-')
    {
        c = getch();
        if (!isdigit(c))
            return getfloat(pn); // Try again since garbage met
    }

    float power = 1.0;

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0');

    if (c == '.')
    {
        c = getch();
        if (!isdigit(c))
            return getfloat(pn);
        for (; isdigit(c); c = getch())
        {
            *pn = 10.0 * *pn + (c - '0');
            power *= 10;
        }
    }

    *pn = (sign * *pn) / power;

    if (c != EOF)
    {
        ungetch(c); // Candidate for next iteration (-, +, for instance)
    }

    return c; // Last digit cought or EOF
}

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
    else if (c != EOF)
        buf[bufp++] = c;
}
