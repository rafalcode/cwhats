#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[])
{
   char *a = "Jul 17, 2016, 2:13:33 PM";

    struct tm tms = {0};
    char *r = strptime(a, "%b %d, %Y, %I:%M:%S %p", &tms);
    // I think I've registered it as a mistake to use %H and %p, you should use %I when %p is also part of string!
    printf("Hour: %d\n", tms.tm_hour);
    printf("Hour: %d\n", tms.tm_hour);


// printf("%s\n", r);
//strptime(a, "%b %d, %Y, %H:%M:%S %p")

   return 0;
}
