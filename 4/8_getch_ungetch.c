/*
* Exercise 4-8. Suppose that there will never be more than one character of pushback. 
* Modify getch and ungetch accordingly.
*/

#include <stdio.h>
#include <string.h>
char buf;
int bufset = 0;

// Run test
// python ./runcc.py -l --comp gcc --sn 4.8 --opts  < ./4/mocks/8_getch_ungetch

/* get a (possibly pushed-back) character */
int getch(void)
{
    if(bufset) {
        bufset = 0;
        return buf; 
    } else {
        return getchar();
    }
}

/* push character back on input */
void ungetch(int c)
{
    buf = c;
    bufset = 1;
}

int main()
{
    char c;
    putchar(getch());
    putchar(getch());
    putchar(getch());
    c = getch();
    putchar(c);
    ungetch(c);
    putchar(getch());
    c = getch();
    if( c == '\n')
    {
        putchar(c);
    }
    return 0;
}