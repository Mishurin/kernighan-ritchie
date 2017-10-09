/*
* Exercise 1-18. Write a program to print all input lines that are longer than 80
* characters.
*/

#include <stdio.h>
#define MAX_LINE_LENGTH 80
#define FILE_LENGTH_LIMIT 1000

// Run to generate testing data:
// 1. python .\textgen.py --length 80  --lines 4 --dest ./1/mocks/80_liner.txt
// 2. python .\textgen.py --length 81  --lines 4 --dest ./1/mocks/80_liner.txt
// Run to test the program:
// python .\runcc.py --comp gcc --sn 1.17 --opts "<" .\1\mocks\80_liner.txt
// Program excludes new line symbol from character sets

int get_line(char line[], int limit);
int copy(char to[], char from[]);

int main() {

    int length;
    char line[MAX_LINE_LENGTH];

    while ((length = get_line(line, FILE_LENGTH_LIMIT)) > 0) {
        if(length > MAX_LINE_LENGTH + 2) {
           printf("%s", line); 
        }
    }

    return 0;
}

int get_line(char line[], int limit) {

    char ch;
    int i;

    for(i = 0; i < limit - 1 && (ch = getchar()) != EOF && ch != '\n'; ++i) {
        line[i] = ch;
    }

    if (ch == '\n') {
        line[i] = ch;
        ++i;
    }

    line[i] = '\0';

    return i;
}

