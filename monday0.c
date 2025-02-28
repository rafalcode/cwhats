// from chag
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void find_mondays(int year, int month)
{
    char formatted_date[100];

    // Initialize tm structure to zero
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));

    // Set the year and month
    tm.tm_year = year - 1900; // tm_year starts from 1900
    tm.tm_mon = month - 1;    // tm_mon is 0-based (0=Jan, 11=Dec)
    tm.tm_mday = 1;           // Start from the 1st day of the month

    tm.tm_isdst = 0;

    // Convert to time_t to determine the first day of the month
    // mktime(&tm);

    // Print the first day of the month
    // strftime(formatted_date, sizeof(formatted_date), "%A %B %d, %Y", &tm);
    strftime(formatted_date, sizeof(formatted_date), "%c", &tm);
    printf("As a test (DST)- first day of %d-%02d: %s\n", year, month, formatted_date);

    // Find the first Monday of the month
    while (tm.tm_wday != 1) { // tm_wday: 0=Sunday, 1=Monday, ..., 6=Saturday
        tm.tm_mday++;  // Move to the next day
        mktime(&tm);   // Update the struct
    }

    // Print all Mondays of the month
    printf("Mondays in %d-%02d:\n", year, month);
    while (tm.tm_mon == month - 1) { // Stay within the same month
        strftime(formatted_date, sizeof(formatted_date), "%a %d %b %Y", &tm);
        printf("  %s\n", formatted_date);
        tm.tm_mday += 7; // Jump to the next Monday
        mktime(&tm);
    }
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Need two args for this one! Two ints: year and the months\n"); 
        exit(EXIT_FAILURE);
    }

    int year=atoi(argv[1]), month=atoi(argv[2]);

    // Validate input
    if (month < 1 || month > 12) {
        printf("Invalid month! Please enter a value between 1 and 12.\n");
        return 1;
    }

    // Find and print Mondays
    find_mondays(year, month);

    return 0;
}
