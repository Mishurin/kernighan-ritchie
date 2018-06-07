/*
* Exercise 4-4. Add the commands to print the top elements of the stack without popping, 
* to duplicate it, and to swap the top two elements. Add a command to clear the stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXOP 100
#define NUMBER '0'
#define COMMAND '1'
#define PRINT_STACK_COMMAND "printstack"
#define DUPLICATE_STACK_COMMAND "duplicatestack"
#define SWAP_FIRST_PAIR_COMMAND "swapfirstpair"
#define CLEAR_STACK_COMMAND "clearstack"
#define DRAW_RULLER_COMMAND "drawruller"
#define RULLER "-----------------------------------------\n"

int getop(char[]);
void push(double);
double pop(void);
void printstack(int);
void duplicatestack(void);
void swapfirstpair(void);
void clearstack(void);
void process_command(char[]);
void drawruller(void);

// Run test
// python ./runcc.py --comp gcc --sn 4.4 --opts < ./4/mocks/4_polish_calc

/* reverse Polish calculator */
int main()
{
    int type;
    double op2;
    char s[MAXOP];
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

void printstack(int num_of_places)
{
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
    int stack_position = sp;
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
    else
        printf("error: unknown command %s\n", command);
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
    if (!isdigit(c) && !isalpha(c) && c != '.' && c != '-')
        return c;

    i = 0;

    /* negative sign or subraction */
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

    char sygnal;

    if (isalpha(c))
    {
        while (isalpha(s[++i] = c = getch()))
            ;
        sygnal = COMMAND;
    }

    if (isdigit(c))
    {
        while (isdigit(s[++i] = c = getch()))
            ;
        if (c == '.')
            while (isdigit(s[++i] = c = getch()))
                ;
        sygnal = NUMBER;
    }

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return sygnal;
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
    else
        buf[bufp++] = c;
}
