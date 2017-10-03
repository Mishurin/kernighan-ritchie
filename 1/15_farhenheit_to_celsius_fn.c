/*
* Exercise 1-15. Rewrite the temperature conversion program of Section 1.2 to use a
* a function for conversion.
*/

#include <stdio.h>

float from_fahr_to_celsius(float f);

int main() {
    float fahr, celsius;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = lower;
    while (fahr <= upper) {
        celsius = from_fahr_to_celsius(fahr);
        printf("%3.0f %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }

    return 0;
}

float from_fahr_to_celsius(float f) {
    return (5.0/9.0) * (f - 32.0);
}