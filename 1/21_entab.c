/*
* Exercise 1-21. Write a program entab that replaces strings of blanks by the minimum
* number of tabs and blanks to achieve the same spacing. Use the same tab stops as
* for detab. When either a tab or a single blank would suffice to reach a tab stop,
* which should be given preference?
*/

// Run to test: 
// python .\runcc.py --comp gcc --sn 1.21 --opts "<" .\1\mocks\spaced_indentation.txt ">" out.txt
// python .\runcc.py --comp gcc --sn 1.21 --opts "<" .\1\mocks\spaced_program.py ">" tabbed_program.py

#include <stdio.h>
#define TABSIZE 4
#define FRAME_MARGIN 2

int get_frame(char s[], int lim);

int main() {
    int length;
    char frame[TABSIZE + FRAME_MARGIN];

    while ((length = get_frame(frame, TABSIZE)) > 0) {
        printf("%s", frame);
    }
    return 0;
}

int get_frame(char s[], int lim) {
    char c;
    int i;
    int trailing_space_count = 0;
    for (i = 0; i < lim && (c = getchar()) != EOF; i++) {
        if (c == ' ') {
            trailing_space_count++;
        } else if (c == '\n') {
            s[i] = c;
            i++;
            break;
        } else {
            trailing_space_count = 0;
        }
        s[i] = c;  
    }

    if (trailing_space_count > 0) {
        int tab_index = lim - trailing_space_count;
        i = tab_index;
        s[i] = '\t';
        i++;
    }

    s[i] = '\0';

    return i;
}

