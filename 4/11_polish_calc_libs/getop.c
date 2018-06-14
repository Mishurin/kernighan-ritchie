#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "calc.h"

/* getop: get next character or numeric operand */
int getop(char s[])
{
    static int lastc = 0;

    int i, c;

    if (lastc == 0)
        c = getch();
    else
    {
        c = lastc;
        lastc = 0;
    }

    while ((s[0] = c) == ' ' || c == '\t')
        c = getch();
    s[1] = END_OF_LINE;
    
    if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-' && c != '=')
        return c;

    i = 0;

    if (c == '=')
    {
        s[i++] = c;
        s[i] = END_OF_LINE;
        return ASSIGNMENT;
    }

    /* negative sign or subraction */
    if (c == '-')
    {
        lastc = getch(); // next
        if (isdigit(lastc))
        {
            s[i++] = '-';
            c = s[i] = lastc;
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
        s[i++] = c;
        if (is_space(lastc))
        {
            signal = VARIABLE;
            s[i] = END_OF_LINE;
            return signal;
        } else {
            s[i] = lastc;
            lastc = 0;
        }

        while (isalpha(s[++i] = c = getch()))
            ;
        signal = COMMAND;
    }

    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
        if (c == '.')
            while (isdigit(s[++i] = c = getch()))
                ;
        signal = NUMBER;
    }

    s[i] = END_OF_LINE;
    if (c != EOF)
        lastc = c;
    return signal;
}

void process_command(char command[])
{
    if (!strcmp(command, PRINT_STACK_COMMAND))
        printstack(-1);
    else if (!strcmp(command, DUPLICATE_STACK_COMMAND))
        duplicatestack();
    else if (!strcmp(command, SWAP_FIRST_PAIR_COMMAND))
        swapfirstpair();
    else if (!strcmp(command, CLEAR_STACK_COMMAND))
        clearstack();
    else if (!strcmp(command, DRAW_RULLER_COMMAND))
        drawruller();
    else if (!strcmp(command, SIN_COMMAND))
        push(sin(pop()));
    else if (!strcmp(command, EXP_COMMAND))
        push(exp(pop()));
    else if (!strcmp(command, POW_COMMAND))
    {
        double op2 = pop();
        push(pow(pop(), op2));
    }
    else
        printf("error: unknown command %s\n", command);
}

void process_variable(char c, double variables[], double last_printed)
{
    if (c >= 'A' && c <= 'Z')
    {
        push(variables[c - 'A']);
    }
    else if (c == 'v')
        push(last_printed);
    else
        printf("error: unknown command");
}

void process_assignment(char c, double variables[])
{
    if (c >= 'A' && c <= 'Z')
    {
        variables[c - 'A'] = pop();
    }
    else
        printf("error: incorrect variable");
}

int is_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}
