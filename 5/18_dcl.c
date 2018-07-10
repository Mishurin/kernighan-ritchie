/*
* Exercise 5-18. Make dcl recover from input errors.
*/

// Run test:
// python ./runcc.py  --comp gcc --sn 5.18 --opts < ./5/mocks/18_dcl.txt

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100
#define MISSINGCLBR '0'
#define MISSINGRPR '1'
#define UNKNOWNTOKEN '2'
#define EOL '\n'

enum
{
    NAME,
    PARENS,
    BRACKETS
};
void dcl(void);
void dirdcl(void);
int gettoken(void);
void jump_to_eol();
int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identifier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];

/* convert declaration to words */
int main()
{
    while (gettoken() != EOF)
    {
        /* 1st token on line */
        /* is the datatype */
        strcpy(datatype, token);
        out[0] = '\0';
        /* parse rest of line */
        dcl();

        if (tokentype == MISSINGCLBR || tokentype == UNKNOWNTOKEN)
        {
            jump_to_eol();
            continue;
        }
        else if(tokentype == MISSINGRPR)
            continue;
        else if (tokentype != EOL)
        {
            jump_to_eol();
            printf("syntax error\n");
            continue;
        }

        printf("%s: %s %s\n", name, out, datatype);
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
    else
        return tokentype = c;
}

/* dcl: parse a declarator */
void dcl(void)
{
    int ns;
    for (ns = 0; gettoken() == '*';) /* count *'s */
        ns++;
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;
    if (tokentype == '(')
    {
        /* ( dcl ) */
        dcl();
        if (tokentype != ')')
        {
            printf("error: missing )\n");
            tokentype = MISSINGRPR;
            return;
        }
    }
    else if (tokentype == NAME) /* variable name */
        strcpy(name, token);
    else if (tokentype == MISSINGCLBR)
        return;
    else
    {
        printf("error: expected name or (dcl)\n");
        tokentype = UNKNOWNTOKEN;
        return;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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
    while ((c = getch()) != '\n' && c != EOF )
        ;
}