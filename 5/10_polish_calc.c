/*
* Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression from 
* the command line, where each operator or operand is a separate argument. For example,
* expr 2 3 4 + *.
*/

// Run test:
// python ./runcc.py -argv --comp gcc --sn 5.10 --opts 2 3 4 + '*'

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define NUMBER '0'
#define END_OF_LINE '\0'
#define MAXOP 100
#define MINARGNUM 3

int getop(char *arg, char *s);
void push(double f);
double pop(void);

int main(int argc, char *argv[])
{
    int type;
    double op2;
    char s[MAXOP];
    
    if (argc < MINARGNUM)
    {
        printf("Error: to few arguments passed. Min number is: %d\n", MINARGNUM);
        return -1;
    }

    while (*++argv != NULL)
    {
        type = getop(*argv, s);
        switch (type)
        {
        case NUMBER:
            push(atof(s));
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
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }

    printf("Result: %f\n", pop());

    return 0;
}

int getop(char *arg, char *s)
{
    static int lastc = 0;
    int type = *arg;

    if (isdigit(*arg) || *arg == '-')
    {
        while (*s++ = *arg++)
            ;
        *s = END_OF_LINE;
        type = NUMBER;
    }

    return type;
}

#define MAXVAL 100
int empty = 1;
double val[MAXVAL];
double *spt = val;

/* push: push f onto value stack */
void push(double f)
{
    if (spt < (val + MAXVAL - 1))
    {
        *spt++ = f;
        empty = 0;
    }
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */

double pop(void)

{
    if (!empty)
    {
        if (spt - 1 == val)
        {
            empty = 1;
        }
        return *--spt;
    }
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
