/*
* Exercise 5-16. Add the -d (``directory order'') option, which makes comparisons only on 
* letters, numbers and blanks. Make sure it works in conjunction with -f.
*/

// Compile:
// gcc -Wall ./5/16_sort.c -o ./5/16_sort
// Run test:
// ./5/16_sort -d -f < ./5/mocks/16_sort.txt

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void q_sort(void *lineptr[], int left, int right,
            int (*comp)(void *, void *),
            int (*predicate)(int, int));
int num_cmp(char *, char *);
int str_cmp(char *, char *);
int str_cmp_dir(char *, char *);
int case_ins_str_cmp(char *, char *);
int case_ins_str_cmp_dir(char *, char *);
int is_dir_char(char);
int gt(int, int);
int lt(int, int);

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;
    int fold = 0;
    int directory = 0;

    while (*++argv != NULL)
    {
        if (str_cmp(*argv, "-n") == 0)
            numeric = 1;
        if (str_cmp(*argv, "-r") == 0)
            reverse = 1;
        if (str_cmp(*argv, "-f") == 0)
            fold = 1;
        if (str_cmp(*argv, "-d") == 0)
            directory = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        q_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? num_cmp : (fold ? 
                (directory ? case_ins_str_cmp_dir : case_ins_str_cmp) : 
                (directory ? str_cmp_dir : str_cmp))),
               (int (*)(int, int))(reverse ? gt : lt));
        writelines(lineptr, nlines);
        return 0;
    }
    else
    {
        printf("input too big to sort\n");
        return 1;
    }
    return 0;
}

// Probably quick sort is not the best choice if you concider to sort an entire 
// array all at once. Sorting by parts may shuffle equivalent strings.
void q_sort(void *v[], int left, int right,
            int (*comp)(void *, void *),
            int (*predicate)(int, int))
{
    int i, last;
    void swap(void *v[], int, int);
    if (left >= right)
        return;
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if ((*predicate)((*comp)(v[i], v[left]), 0))
            swap(v, ++last, i);
    }
    swap(v, left, last);
    q_sort(v, left, last - 1, comp, predicate);
    q_sort(v, last + 1, right, comp, predicate);
}

int num_cmp(char *s1, char *s2)
{
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

int str_cmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int str_cmp_dir(char *s, char *t)
{
    char a = 0;
    char b = 0;
    while (a == b)
    {
        while (!is_dir_char(*s) && *s != '\0')
            s++;
        while (!is_dir_char(*t) && *t != '\0')
            t++;
        a = *s;
        b = *t;
        if (a == '\0' || b == '\0')
            break;
        s++;
        t++;
    }
    return a - b;
}

int case_ins_str_cmp(char *s, char *t)
{
    for (; tolower(*s) == tolower(*t); s++, t++)
        if (*s == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}

int case_ins_str_cmp_dir(char *s, char *t)
{
    char a = 0;
    char b = 0;
    while (a == b)
    {
        while (!is_dir_char(*s) && *s != '\0')
            s++;
        while (!is_dir_char(*t) && *t != '\0')
            t++;
        a = tolower(*s);
        b = tolower(*t);
        if (a == '\0' || b == '\0')
            break;
        s++;
        t++;
    }
    return a - b;
}

int is_dir_char(char a)
{
    return isalnum(a) || isspace(a);
}

int gt(int a, int b)
{
    return a > b;
}

int lt(int a, int b)
{
    return a < b;
}

void swap(void *v[], int i, int j)
{
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000 /* max length of any input line */
int get_line(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];
    nlines = 0;
    while ((len = get_line(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else
        {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    return nlines;
}

void writelines(char *lineptr[], int nlines)
{
    int i;
    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

int get_line(char *s, int lim)
{
    int c, i;

    for (i = 0; --lim && (c = getchar()) != EOF && c != '\n'; s++, i++)
    {
        *s = c;
    }

    if (c == '\n')
    {
        *s++ = c;
        i++;
    }

    *s = '\0';
    return i;
}

#define ALLOCSIZE 10000
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;
char *alloc(int n)
{
    if (allocbuf + ALLOCSIZE - allocp >= n)
    {
        allocp += n;
        return allocp - n;
    }
    else
        return 0;
}