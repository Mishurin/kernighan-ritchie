/*
* Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid 
* representation of zero. Fix it to push such a character back on the input.
*/

// Run test
// python ./runcc.py --comp gcc --sn 5.1 --opts  < ./5/mocks/1_getint | head

#include <stdio.h>
#include <ctype.h>
#define SIZE 1000

int n, array[SIZE], getint(int *);

int main()
{
    for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
        ;
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d\n", array[i]);
    }
    return 0;
}

int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
// Improved version
int getint(int *pn)
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
            return getint(pn); // Try again since garbage met
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

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
