/*
* Excercise 1-4. Write a program to print the corresponding Celsius to Fahrenheit table.
*/

#include <stdio.h>

int main() {
    
    float celsius, fahr;
    int start = 0, end = 300, step = 20;

    celsius = start;
    printf("%12s\t%12s\n", "----------", "----------");
    printf("%12s\t%12s\n", "Celsius", "Fahrenheit");
    printf("%12s\t%12s\n", "----------", "----------");
    while (celsius <= end) {
        fahr = 9.0/5.0 * celsius + 32;
        printf("%12.0f\t%12.1f\n", celsius, fahr);
        celsius += step;
    }

    return 0;
}