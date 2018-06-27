/*
* Exercise 5-9. Rewrite the routines day_of_year and month_day with pointers instead of 
* indexing.
*/

// Run test:
// python ./runcc.py --comp gcc --sn 5.9

#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main()
{
    printf("Result: %d\n", day_of_year(2018, 6, 26));
    printf("Result: %d\n", day_of_year(2018, 6, 27));
    int month, day;
    month_day(2018, 177, &month, &day);
    printf("Result: month=%d, day=%d\n", month, day);
    month_day(2018, 178, &month, &day);
    printf("Result: month=%d, day=%d\n", month, day);
    return 0;
}

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
    int i, leap;
    char *mpt, *cmpt;

    if (year <= 0 || month <= 0 || month > 12 || day <= 0 || day > 31)
    {
        return -1;
    }
    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    mpt = *(daytab + leap);
    cmpt = mpt + month;
    if (day > *cmpt)
    {
        return -1;
    }
    while (++mpt < cmpt)
        day += *mpt;
    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;
    char *mpt;
    if (year <= 0 || yearday <= 0 || yearday > 366)
    {
        printf("Error: invalid input: year=%d, yearday=%d\n", year, yearday);
        return;
    }

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    mpt = *(daytab + leap);

    if (!leap && yearday > 365)
    {
        printf("Non-leap year has only 365 days\n");
    }

    for (i = 1; yearday > *(++mpt); i++)
        yearday -= *mpt;
    *pmonth = i;
    *pday = yearday;
}