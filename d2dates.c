// from chag
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define D1970 "01011970" // because epoch seconds for 01011970 will decide the sys tem offset

void valinput(int dd, int mm)
{
    // Validate input
    if (mm < 1 || mm > 12) {
        printf("Invalid month! Please enter a value equal to or between 1 and 12.\n");
        exit(EXIT_FAILURE);
    } else if (dd < 1 || dd > 31) {
        printf("Invalid day! Please enter a value  equal to or between 1 and 31.\n");
        exit(EXIT_FAILURE);
    }
}

int printes(struct tm *tm0, struct tm *tm2, int offset)
{
    char *tf = calloc(128, sizeof(char));
    char *tf2 = calloc(128, sizeof(char));
    // tm0.tm_isdst = 0;

    // Convert to time_t to determine the first day of the month
    // mktime(tm0);

    strftime(tf, 128*sizeof(char), "%c", tm0);
    printf("arg1: %s\n", tf);
    memset(tf, 0, 128*sizeof(char));

    // mktime(tm0);
    strftime(tf, 128*sizeof(char), "%s", tm0);
    int epsecs0 = atoi(tf) +offset;
    printf("arg1: %s\n", tf);

    strftime(tf2, 128*sizeof(char), "%c", tm2);
    printf("arg2: %s\n", tf2);
    memset(tf2, 0, 128*sizeof(char));

    strftime(tf2, 128*sizeof(char), "%s", tm2);
    int epsecs2 = atoi(tf2) +offset;
    printf("arg2: %s\n", tf2);
    printf("arg2:%i -arg1:%i in epseconds: %i\n", epsecs2, epsecs0, epsecs2 - epsecs0);
    int diff = epsecs2 - epsecs0;

    free(tf);
    free(tf2);

    return diff;
}

int systoff(char *instr) // by how many seconds is the current system's (locale) time off in seconds?
{
    struct tm *tm0=calloc(1, sizeof(struct tm));
    int dd, mm, yyyy;
    sscanf(instr, "%2d%2d%4d", &dd, &mm, &yyyy);
    tm0->tm_mday=dd;
    tm0->tm_mon=mm-1;
    tm0->tm_year=yyyy -1900;
    tm0->tm_isdst = 1;

    char *tf = calloc(128, sizeof(char));
    // tm0.tm_isdst = 0;

    // Convert to time_t to determine the first day of the month
    // mktime(tm0);

    strftime(tf, 128*sizeof(char), "%c", tm0);
    printf("D1970: %s\n", tf);
    memset(tf, 0, 128*sizeof(char));

    // mktime(tm0);
    strftime(tf, 128*sizeof(char), "%s", tm0);
    printf("D1970: %s\n", tf);

    int offset = -atoi(tf);
    free(tf);
    free(tm0);
    return offset;
}

int main(int argc, char **argv)
{
    if(argc != 3) {
        printf("Need two args for this one! Two dates in DDMMYYY year form\n"); 
        exit(EXIT_FAILURE);
    }

    int offset = systoff(D1970);
    printf("offset = %i\n", systoff(D1970));

    int dd, mm, yyyy;

    // first arg
    sscanf(argv[1], "%2d%2d%4d", &dd, &mm, &yyyy);
    valinput(dd, mm);
    struct tm *tm1=calloc(1, sizeof(struct tm));
    tm1->tm_mday=dd;
    tm1->tm_mon=mm-1;
    tm1->tm_year=yyyy -1900;
    tm1->tm_isdst = 1;
    // mktime(tm1);
    
    // sec arg
    sscanf(argv[2], "%2d%2d%4d", &dd, &mm, &yyyy);
    valinput(dd, mm);
    struct tm *tm2=calloc(1, sizeof(struct tm));
    tm2->tm_mday=dd;
    tm2->tm_mon=mm-1;
    tm2->tm_year=yyyy -1900;
    tm2->tm_isdst = 0;

    // print difference in seconds
    int diff = printes(tm1, tm2, offset);
    printf("Difference in days = %i.\n", diff/86400);
    free(tm1);
    free(tm2);

    return 0;
}
