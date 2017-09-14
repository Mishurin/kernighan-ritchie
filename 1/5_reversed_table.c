/*
* Excercise 1-5. Modify the temperature conversion program to print the table in reversed order,
* that is, from 300 degrees to 0
*/

#include <stdio.h>

int main() {

    int fahr;

    printf("%12s\t%12s\n", "----------", "----------");
    printf("%12s\t%12s\n", "Fahrenheit", "Celsius");
    printf("%12s\t%12s\n", "----------", "----------");

    for (int fahr = 300; fahr >= 0; fahr -= 20) {
        printf("%12d\t%12.1f\n", fahr, (5.0/9.0) * (fahr - 32));
    }

    return 0;
}