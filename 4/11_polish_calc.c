/*
* Exercise 4-11. Modify getop so that it doesn't need to use ungetch. Hint: use an internal 
* static variable.
*/

// Run test:
// python ./runcc.py -l --i ./4/11_polish_calc_libs/ --inc ./11_polish_calc_libs/getch.c ./11_polish_calc_libs/getop.c ./11_polish_calc_libs/stack.c --comp gcc--sn 4.11 --opts  < ./4/mocks/11_polish_calc

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100
int ignoreeol = 0;


/* reverse Polish calculator */
int main()
{
    extern int ignoreeol;
    int type;
    double op2;
    char s[MAXOP];
    double variables[VARIABLES_MAX_RANGE];
    double last_printed = 0;
    char last_variable;
    while ((type = getop(s)) != EOF)
    {
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
        case COMMAND:
            process_command(s);
            break;
        case VARIABLE:
            process_variable(s[0], variables, last_printed);
            last_variable = s[0];
            break;
        case ASSIGNMENT:
            process_assignment(last_variable, variables);
            pop(); // Remove garbage
            break;
        case '\n':
            if (!ignoreeol)
            {
                last_printed = pop();
                printf("\t%.8g\n", last_printed);
            }
            else
                ignoreeol = 0;
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}
