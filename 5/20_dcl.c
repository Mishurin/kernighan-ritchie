/*
* Exercise 5-20. Expand dcl to handle declarations with function argument types, qualifiers 
* like const, and so on.
*/

// Run test:
// python ./runcc.py  --comp gcc --sn 5.20 --opts < ./5/mocks/20_dcl.txt

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100
#define MISSINGCLBR '0'
#define MISSINGRPR '1'
#define UNKNOWNTOKEN '2'
#define EOL '\n'
#define EOS '\0'

enum
{
    NAME,
    PARENS,
    BRACKETS,
    TYPE,
    QUALIFIER
};

static char *types[] = {
    "void",
    "int",
    "long",
    "signed",
    "unsigned",
    "float",
    "double",
    "char"};

static char *qualifiers[] = {
    "static",
    "const"};

void dcl(char *name, char *out);
void dirdcl(char *name, char *out);
int gettoken(void);
void jump_to_eol();
void ungets(char *s);
int strindex(char *s, char *t);
int find_token(char *token, char *tokens[]);
int get_types_and_qualifiers(char *store);
int get_declaration(int pos);
void print_buffer();
void clean_buffer();
void add_tabs(int n);
int tokentype;
char token[MAXTOKEN];
int level = 0;
char buffer[10][100][3][100];
char bufout[1000];

/* convert declaration to words */
int main()
{
    while (get_declaration(0))
    {
        print_buffer(0);
        clean_buffer();
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
            strcpy(token, "(");
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

        *p = EOS;
        return tokentype = BRACKETS;
    }
    else if (isalpha(c) || c == '_')
    {
        for (*p++ = c; isalnum(c = getch()) || c == '_';)
            *p++ = c;
        *p = EOS;
        ungetch(c);
        if (find_token(token, types))
            return tokentype = TYPE;
        else if (find_token(token, qualifiers))
            return tokentype = QUALIFIER;
        else
            return tokentype = NAME;
    }
    else
    {
        *p++ = c;
        *p = EOS;
        return tokentype = c;
    }
}

/* dcl: parse a declarator */
void dcl(char *name, char *out)
{
    int ns;
    for (ns = 0; gettoken() == '*';) /* count *'s */
        ns++;
    dirdcl(name, out);
    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(char *name, char *out)
{
    int type;
    if (tokentype == '(')
    {
        /* ( dcl ) */
        dcl(name, out);
        if (tokentype != ')')
        {
            printf("error: missing )\n");
            tokentype = MISSINGRPR;
            return;
        }
    }
    else if (tokentype == NAME)
        strcpy(name, token);
    else if (tokentype == MISSINGCLBR)
        return;
    else if (tokentype == ',')
        return;
    else if (tokentype == ')')
        return;
    else
    {
        printf("error: expected name or (dcl)\n");
        tokentype = UNKNOWNTOKEN;
        return;
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
    {
        if (type == '(')
        {
            int pos = 0;
            strcat(out, " function with params");
            do
            {
                get_declaration(pos++);
            } while (tokentype == ',');
            if (tokentype != ')')
            {
                printf("error: missing )\n");
                tokentype = MISSINGRPR;
                return;
            }
        }
        else if (type == PARENS)
            strcat(out, " function returning");
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
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
    while ((c = getch()) != '\n' && c != EOF)
        ;
}

void ungets(char *s)
{
    int slen = strlen(s);
    while (--slen >= 0)
    {
        ungetch(*(s + slen));
    }
}

int strindex(char *s, char *t)
{
    int i, k;
    for (i = 0; *s != '\0'; i++)
    {
        char *pts = s;
        char *ptt = t;
        for (k = 0; *ptt != '\0' && *pts == *ptt; pts++, ptt++, k++)
            ;
        if (k > 0 && *ptt == '\0')
            return i;
        s++;
    }
    return -1;
}

int find_token(char *token, char *tokens[])
{
    while (*tokens != NULL)
    {
        if (strcmp(token, *tokens) == 0)
        {
            return 1;
        }
        tokens++;
    }
    return 0;
}

int get_declaration(int pos)
{
    char name[MAXTOKEN];

    char datatype[MAXTOKEN];
    char out[MAXTOKEN];
    out[0] = '\0';

    get_types_and_qualifiers(datatype);

    if (tokentype == EOF)
        return 0;
    else
    {
        level++;
        dcl(name, out);
        level--;
        if (tokentype == MISSINGCLBR || tokentype == UNKNOWNTOKEN)
        {
            jump_to_eol();
            return 1;
        }
        else if (tokentype == MISSINGRPR)
            return 1;
        else if (tokentype != EOL && tokentype != ',' && tokentype != ')')
        {
            jump_to_eol();
            printf("syntax error\n");
            return 1;
        }

        sprintf(buffer[level][pos][0], "%s", name);
        sprintf(buffer[level][pos][1], "%s", out);
        sprintf(buffer[level][pos][2], "%s", datatype);
        return 1;
    }
}

int get_types_and_qualifiers(char *store)
{
    int count = 0;
    int type;
    while ((type = gettoken()) == TYPE || type == QUALIFIER)
    {
        sprintf(store, "%s", token);
        count++;
    }
    ungets(token);
    return count;
}


void print_buffer(int level)
{
    for (int i = 0, size = sizeof(buffer[level]) / sizeof(buffer[level][0]); i < size; i++)
    {
        char *pname = buffer[level][i][0];
        char *pout = buffer[level][i][1];
        char *pdtype = buffer[level][i][2];
        if (strlen(pname) || strlen(pout) || strlen(pdtype))
        {
            char temp[1000];
            add_tabs(level);
            sprintf(temp, "%s:", strlen(pname) > 0 ? pname : "@anonymous");
            strcat(bufout, temp);
            if (strindex(pout, "function with params") != -1)
            {
                sprintf(temp, "%s %s", pout, ": [\n");
                strcat(bufout, temp);
                print_buffer(level + 1);
                add_tabs(level);
                sprintf(temp, "%s", "] that returns");
                strcat(bufout, temp);
            }
            else
            {
                strcat(bufout, pout);
            }
            sprintf(temp, " %s\n", pdtype);
            strcat(bufout, temp);
        }
    }
    if (level == 0)
    {
        printf("%s", bufout);
    }
}

void clean_buffer()
{
    memset(buffer, 0, sizeof(buffer));
    memset(bufout, 0, sizeof(bufout));
}


void add_tabs(int n)
{
    if (n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            strcat(bufout, "\t");
        }
    }
}