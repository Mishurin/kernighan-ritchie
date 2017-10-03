/*
* Exercise 1-11. How would you test the word count program? 
* What kinds of input are most likely to uncover bugs if there any
*/

#include <stdio.h>

#define IN 1
#define OUT 0

// 1. 
// To run and test the program execute in the root: 
// python .\runcc.py --comp gcc --sn 1.11 --opts "<" .\1\mocks\wc_valid_data.txt
// "<" quoted to use it with window power shell
// 2.
// To compare the results with onses that can be retreived with "wc" run:
// wc .\1\mocks\wc_valid_data.txt
// Results should be similar
// 3 32 162 (for c program)
// 3  32 162 .\1\mocks\wc_valid_data.txt (for wc)
// 3.
// Testing empty file:
// python .\runcc.py --comp gcc --sn 1.11 --opts "<" .\1\mocks\wc_empty.txt
// 4.
// Tests if executable file is also readable (tests iself in this case)w:
// python .\runcc.py --comp gcc --sn 1.11 --opts "<" .\1\11_wc_testing.exe
// Output: 195 1169 58952
// 5. Run with wc:
// wc .\1\11_wc_testing.exe
// Output: 195  1704 58952 .\1\11_wc_testing.exe
int main() {
    
    int c, nl, nw, nc, state;

    state = OUT;
    nl = nw = nc = 0;
    while ((c = getchar()) != EOF) {
        ++nc;
        if (c == '\n')
            ++nl;
        if (c == ' ' || c == '\n' || c == '\t')
            state = OUT;
        else if (state == OUT) {
            state = IN;
            ++nw;
        }
    }
    printf("%d %d %d\n", nl, nw, nc);
    return 0;
}