/*
* Exercise 1-19. Write a function reverse(s) that reverses the character
* string s. Use it to write a program that reverses its intput a line 
* at a time
*/

#include <stdio.h>
#define MAXLINE 1000

// Run to test program:
// python .\runcc.py --comp gcc --sn 1.19 --opts "<" .\1\mocks\reversed_words.txt

int len(char s[]);
void copy(char to[], char from[]);
void reverse(char s[]);
int get_line(char line[], int maxline);

int main() {
    int length;
    char line[MAXLINE];
    while ((length = get_line(line, MAXLINE)) > 0) {
        reverse(line);
        printf("%s", line);
    }
    return 0;
}

void reverse(char s[]) {
    int length = len(s);
    char s_copy[length];
    copy(s_copy, s);
    for (int i = length - 1, k = 0; i >= 0; i--, k++) {
        s[k] = s_copy[i];
    }
}

int len(char s[]) {
    char c;
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

void copy(char to[], char from[]) {
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
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