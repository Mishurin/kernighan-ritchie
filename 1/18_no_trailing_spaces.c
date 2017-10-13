/*
* Exercise 1-18. Write a program to remove trailing blanks and tabs from each line of
* input, and to delete entirily blank lines.
*/

// Run test with:
// python .\runcc.py --comp gcc --sn 1.18 --opts "<" .\1\mocks\trailing_spaces.txt ">" out.txt

#include <stdio.h>
#define MAXLINE 1000
#define IS_WINDOWS 1
#define IS_UNIX 0
#define LINE_HAS_CHARACTERS 1
#define LINE_IS_EMPTY 0

void copy(char to[], char from[]);
int get_line(char line[], int maxline);
void trim_trailing_blanks(char line[], int length);

int main() {
    char line[MAXLINE];
    char save[MAXLINE];
    int length;

    while ((length = get_line(line, MAXLINE)) > 0) {
        trim_trailing_blanks(line, length);
        printf("%s", line);
    }

    return 0;
}

void trim_trailing_blanks(char line[], int length) {
    int is_windows = IS_UNIX;
    int has_line_characters = LINE_IS_EMPTY;
    for (int i = length - 1; i >= 0; i--) {
        char ch = line[i];
        if (ch == '\r') {
            is_windows = IS_WINDOWS;
        }
        if (line[i] != '\r' && line[i] != '\n' && line[i] != '\t' && line[i] != ' ') {
            has_line_characters = LINE_HAS_CHARACTERS;
            if(is_windows) {
                line[++i] = '\r';    
            }
            line[++i] = '\n';
            line[++i] = '\0';
            break;
        }
    }

    if(!has_line_characters) {
        line[0] = '\0';
    }

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