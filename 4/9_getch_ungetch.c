/*
* Exercise 4-9. Our getch and ungetch do not handle a pushed-back EOF correctly. Decide 
* what their properties ought to be if an EOF is pushed back, then implement your design.
*/

#include <stdio.h>
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;

// Run test
// python ./runcc.py -l --comp gcc --sn 4.9 --opts  < ./4/mocks/9_getch_ungetch

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
    else if(c != EOF)
        buf[bufp++] = c;
}

int main()
{
    char c = getch();
    ungetch(c);
    printf("EOF: %c\n", getch());
    ungetch(-1); // Pushed literaly
    c = getch();
    printf("EOF again: %c\n",c);
    return 0;
}
