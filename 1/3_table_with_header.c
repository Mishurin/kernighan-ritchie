/*
* Modify the temperature conversion program to print a heading above table.
*/

#include <stdio.h>

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    printf("%12s\t%12s\n", "----------", "----------");
    printf("%12s\t%12s\n", "Fahrenheit", "Celsius");
    printf("%12s\t%12s\n", "----------", "----------");
    while (fahr <= upper) {
        celsius = (5.0/9.0) * (fahr - 32);
        printf("%12.0f\t%12.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
    return 0;
}

