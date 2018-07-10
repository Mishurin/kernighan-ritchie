/*
* Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 5.19 --opts < ./5/mocks/19_undcl.txt

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MISSINGCLBR '0'
#define MAXTOKEN 100
#define EOL '\n'

enum
{
    NAME,
    PARENS,
    BRACKETS,
    STAR
};
int gettoken(void);
void ungetch(int);
void jump_to_eol();
int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identifier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];

/* undcl: convert word descriptions to declarations */
int main()
{
    int type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while ((type = gettoken()) != EOL && type != EOF)
        {
            if (type == PARENS || type == BRACKETS)
                strcat(out, token);
            else if (type == STAR)
            {
                int nexttoken = gettoken();
                if (nexttoken == BRACKETS || nexttoken == PARENS)
                {
                    sprintf(temp, "(*%s)", out);
                }
                else
                {
                    sprintf(temp, "*%s", out);
                }

                strcpy(out, temp);
                char *tpt = token;
                int tlen = strlen(token);
                while (--tlen >= 0)
                {
                    ungetch(*(tpt + tlen));
                }
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
                jump_to_eol();
                tokentype = EOL;
            }
        }
        printf("%s\n", out);
    }

    return 0;
}

/* return next token */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    while ((c = getch()) == ' ' || c == '\t')
        ;
    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (c = getch()) != ']' && c != EOL && c != EOF;)
            *p++ = c;
        if (c == ']')
        {
            *p++ = c;
        }
        else
        {
            printf("error: closing ] is missing\n");
            tokentype = MISSINGCLBR;

            if (c == EOL)
                ungetch(EOL);

            return tokentype;
        }

        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
            *p++ = c;
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else if (c == '*')
    {
        *p++ = '*';
        *p = '\0';
        return tokentype = STAR;
    }
    else
        return tokentype = c;
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
    else if (c != EOF)
        buf[bufp++] = c;
}

void jump_to_eol()
{
    char c;
    while ((c = getch()) != '\n' && c != EOF)
        ;
}