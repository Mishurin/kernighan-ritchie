/*
* Exercise 1-16. Revise the main routine of the longest-line program so it
* will correctly print the length of arbitrarily long input, and as much
* as possible of the text
*/

#include <stdio.h>
#define MAXLINE 1000

// getline - is a function from stdio library, that is the reason 
// to rename give our custom function another name
// To avoid get_line and copy function modification we add a new
// implementation of get_line which addresses the requirement
// To generate test file run script:
// python .\textgen.py --mode r --length 100 --dest ./1/mocks/long_liner.txt
// or
// python .\textgen.py --length 100 --dest ./1/mocks/long_liner.txt
// Test program with:
// python .\runcc.py --comp gcc --sn 1.16 --opts "<" .\1\mocks\long_liner.txt
// Test correctness
// wc .\1\mocks\long_liner.txt

int get_line(char line[], int maxline);
int get_line_and_full_length(char line[], int maxline);

void copy(char to[], char from[]);

int main() {
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = get_line_and_full_length(line, MAXLINE)) > 0) {
        if (len > max) {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("Longest line:\n");
        printf("%s\n", longest);
        printf("Length:");
        printf("%d\n", max);
    }
    return 0;
}

int get_line_and_full_length(char s[], int lim) {
    
    int c, i, k;

    for (i = 0, k = 0; (c = getchar()) != EOF && c != '\n'; i++, k++) {
        if (i < lim - 1) {
            s[i] = c;
        }
    }
    
    if (c == '\n') {
        s[i] = c;
        ++i;
        ++k;
    }

    s[i] = '\0';

    return k;

} 

int get_line(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
        s[i] = c;        
    }
    
    if( c == '\n') {
        s[i] = c;
        ++i;
    }

    s[i] = '\0';
    return i;
}

void copy(char to[], char from[]) {
    int i;
    
    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}