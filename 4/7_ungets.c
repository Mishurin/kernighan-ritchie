/*
* Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the 
* input. Should ungets know about buf and bufp, or should it just use ungetch?
*/

#include <stdio.h>
#include <string.h>
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

void reverse(char s[])
{
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void ungets(char s[])
{
    int i = 0;
    reverse(s); // Needed since getch starts from the right end
    while (s[i] != '\0')
    {
        ungetch(s[i]);
        i++;
    }
}

int main()
{
    char c;
    char input[BUFSIZE];
    int i = 0;
    while ((c = getch()) != EOF)
    {
        input[i] = c;
        i++;
    }
    input[i] = '\0';
    printf("Input:%s\n", input);
    printf("Buffer:%s\n", buf);

    ungets(input);
    printf("Buffer:%s\n", buf);

    i = 0;
    while ((c = getch()) != EOF)
    {
        input[i] = c;
        i++;
    }

    input[i] = '\0';
    printf("Input:%s\n", input);
    return 0;
}