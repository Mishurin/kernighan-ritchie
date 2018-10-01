/*
* Exercise 5-5. Rewrite the postfix calculator of Chapter 4 to use scanf and/or 
* sscanf to do the input and number conversion.
*/

// Run test
// python ./runcc.py --comp gcc --sn 7.5 --opts < ./7/mocks/5_polish_calc.txt

#include <stdio.h>
#include <stdlib.h>
#define MAXOP 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
    float number;
    while ((type = getop(s)) != EOF)
    {
        switch (type)
        {
        case NUMBER:
            sscanf(s, "%f", &number);
            push(number);
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error: zero divisor\n");
            break;
        case '%':
            op2 = pop();
            push((int)pop() % (int)op2);
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100
int sp = 0;
double val[MAXVAL];

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}

#include <ctype.h>
int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.' && c != '-')
        return c;

    i = 0;

    /* negative sign or subtraction */
    if (c == '-')
    {
        c = getch(); // next
        if (isdigit(c))
        {
            s[i] = '-';
            ungetch(c); // unread spied to live fancy while loops intact
        }
        else
        {
            ungetch(c);
            return '-';
        }
    }

    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;

    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

/* get a (possibly pushed-back) character */
int getch(void)
{
    char c;
    if (bufp > 0)
        return buf[--bufp];
    else
        return scanf("%c", &c) > 0? (int)c : EOF;
}

/* push character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
