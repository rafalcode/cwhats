/* takes 6 digits and assumes it's a time, and will output epoch seconds
 * this is usefull for getting linear differences between times without worrying about the sexigesimals suchas mins and secs.
*/
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>

#define THROWAWAYMEMSZ 128

int main (int argc, char *argv[])
{
    
    // struct tm *mtime = localtime(&ifsta.st_mtime);
    // what is struct tm?
    //int    tm_sec   seconds [0,61]
    //int    tm_min   minutes [0,59]
    //int    tm_hour  hour [0,23]


    char *anytime="142233";
    int h,m,s;
    // sscanf(anytime, "%2d%2d%2d", &h, &m , &s);
    struct tm mytime;
    sscanf(anytime, "%2d%2d%2d", &mytime.tm_hour, &mytime.tm_min, &mytime.tm_sec);
    // if there were tokens between the components such as 14:22:33 the 2 in %2d would not necessary
    // as in:
    // sscanf(anytime, "%d:%d:%d", &mytime.tm_hour, &mytime.tm_min, &mytime.tm_sec);

    printf("%i\n", s); 

    // mytime.tm_sec=33;
    // mytime.tm_min=22;
    // mytime.tm_hour=14;

    // the following are fillers, 01/01/1970 is a standard date, makes everything paly blla
    mytime.tm_mday=1;
    mytime.tm_mon=0;
    mytime.tm_year=70;

    // Create a buffer to hold the formatted time string
    char *mtime_str=calloc(THROWAWAYMEMSZ, sizeof(char));
    // if (strftime(mtime_str, THROWAWAYMEMSZ, "%H:%M:%S", &mytime) == 0) {
    if (strftime(mtime_str, THROWAWAYMEMSZ, "%s", &mytime) == 0) {
        fprintf(stderr, "strftime returned 0");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", mtime_str);
    free(mtime_str);

    return 0;
}
