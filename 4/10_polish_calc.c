/*
* Exercise 4-10. An alternate organization uses get_line to read an entire input line; 
* this makes getch and ungetch unnecessary. Revise the calculator to use this approach.
*/

// Run test
// python ./runcc.py -l --comp gcc --sn 4.10--opts  < ./4/mocks/10_polish_calc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_LINE_LENGTH 100
#define MAXOP 100
#define NUMBER '0'
#define COMMAND '1'
#define VARIABLE '2'
#define ASSIGNMENT '3'
#define END_OF_LINE '\0'
#define VARIABLES_MAX_RANGE 26
#define PRINT_STACK_COMMAND "printstack"
#define DUPLICATE_STACK_COMMAND "duplicatestack"
#define SWAP_FIRST_PAIR_COMMAND "swapfirstpair"
#define CLEAR_STACK_COMMAND "clearstack"
#define DRAW_RULLER_COMMAND "drawruller"
#define SIN_COMMAND "sin"
#define EXP_COMMAND "exp"
#define POW_COMMAND "pow"
#define RULLER "-----------------------------------------\n"

int getop(char[], char[]);
void push(double);
double pop(void);
void printstack(int);
void duplicatestack(void);
void swapfirstpair(void);
void clearstack(void);
void process_command(char[]);
void process_variable(char, double[], double);
void process_assignment(char, double[]);
void drawruller(void);
int get_line(char[], int);

int cpos = 0;
int ignoreeol = 0;

/* reverse Polish calculator */
int main()
{
    extern int ignoreeol;
    int type, length;
    double last_printed = 0, op2, variables[VARIABLES_MAX_RANGE];
    char last_variable, s[MAXOP], line[MAX_LINE_LENGTH];
    while (get_line(line, MAX_LINE_LENGTH) > 0)
    {
        cpos = 0;
        while ((type = getop(line, s)) != END_OF_LINE)
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
                {
                    ignoreeol = 0;
                }
                break;
            default:
                printf("error: unknown command %s\n", s);
                break;
            }
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

#include <ctype.h>

int is_space(char);
/* getop: get next character or numeric operand */
int getop(char input[], char s[])
{
    extern int cpos;
    int i = 0, j, c, next;
    s[1] = END_OF_LINE;

    for (j = cpos; input[j] != END_OF_LINE; j++)
    {
        cpos++;
        c = input[j];
        if (c == ' ' || c == '\t')
            continue;

        if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-' && c != '=')
        {
            s[i] = c;
            return c;
        }

        if (c == '=')
        {
            s[i] = c;
            return ASSIGNMENT;
        }

        next = input[j + 1];

        if (c == '-')
        {
            if (isdigit(next))
                s[i++] = '-';
            else
                return '-';
        }

        if (isdigit(c) || c == '.')
        {
            s[i++] = c;
            if (!isdigit(next) && next != '.')
            {
                s[i++] = END_OF_LINE;
                return NUMBER;
            }
        }

        if (isalpha(c))
        {
            s[i++] = c;
            if (!isalpha(next) && i > 1)
            {
                s[i++] = END_OF_LINE;
                return COMMAND;
            }
            else if (is_space(next))
                return VARIABLE;
        }
    }

    if (input[j] == END_OF_LINE)
        return END_OF_LINE;
}

int is_space(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n';
}

int get_line(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
    {
        s[i] = c;
    }

    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}
