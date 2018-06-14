#include <stdio.h>
#include "calc.h"

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

void printstack(int num_of_places)
{
    extern int ignoreeol;
    ignoreeol = 1;
    int top = num_of_places != -1 ? num_of_places : sp;
    top = (top > MAXVAL || top > sp) ? sp : top;
    int i = 0;
    printf("Stack: ");
    for (; i < top; i++)
    {
        printf("[%d:%f]", i, val[i]);
    }
    printf("\n");
    printf("Total: %d\n", i);
}

void duplicatestack(void)
{
    extern int ignoreeol;
    ignoreeol = 1;
    int stack_position = sp;
    if (stack_position * 2 <= MAXVAL)
    {
        for (int i = 0, k = stack_position; i < stack_position; i++, k++)
        {
            val[k] = val[i];
            sp++;
        }
    }
    else
        printf("error: Cannot duplicate stack since number of duplicated items will exceede limit:%d\n", MAXVAL);
}

void swapfirstpair(void)
{
    extern int ignoreeol;
    ignoreeol = 1;
    double temp;
    if (sp >= 2)
    {
        temp = val[1];
        val[1] = val[0];
        val[0] = temp;
    }
    else
        printf("error: Not enough items in stack to perform swap");
}

void clearstack(void)
{
    extern int ignoreeol;
    ignoreeol = 1;
    for (int i = 0; i < sp; i++)
    {
        val[i] = 0;
        sp--;
    }
    sp = 0;
    printf("stack is empty\n");
}

void drawruller(void)
{
    extern int ignoreeol;
    ignoreeol = 1;
    printf(RULLER);
}