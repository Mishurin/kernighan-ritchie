/*
*   Exercise 5-15. Add the option -f to fold upper and lower case together, so that case 
* distinctions are not made during sorting; for example, a and A compare equal.
*/

// Compile:
// gcc -Wall ./5/15_sort.c -o ./5/15_sort
// Run test:
// ./5/15_sort -f < ./5/mocks/15_sort.txt

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
int case_ins_str_cmp(char *, char *);
int gt(int, int);
int lt(int, int);

int main(int argc, char *argv[])
{
    int nlines;
    int numeric = 0;
    int reverse = 0;
    int fold = 0;

    while (*++argv != NULL)
    {
        if (str_cmp(*argv, "-n") == 0)
            numeric = 1;
        if (str_cmp(*argv, "-r") == 0)
            reverse = 1;
        if (str_cmp(*argv, "-f") == 0)
            fold = 1;
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
    {
        q_sort((void **)lineptr, 0, nlines - 1,
               (int (*)(void *, void *))(numeric ? 
                    num_cmp : (fold ? case_ins_str_cmp : str_cmp)),
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

int case_ins_str_cmp(char *s, char *t)
{
    for (; tolower(*s) == tolower(*t); s++, t++)
        if (*s == '\0')
            return 0;
    return tolower(*s) - tolower(*t);
}

int gt(int a, int b){
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