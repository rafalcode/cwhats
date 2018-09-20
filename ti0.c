/* playing with c's time function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __USE_XOPEN // because strptime not recognised otherwise
#include <time.h>

#define STRSZ 128

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if((argc!=2) & (argc !=3)){
        printf("Usage: prints DD ## MM YYYY dates day by day.\n"); 
        printf("if you give just one argument, its the number of days up to currdate\n");
        printf("if you give two, the second arg is the day from which you want arg1 days counted\n");
        exit(EXIT_FAILURE);
    }
    long daysago=atol(argv[1]);

    time_t rawtime;
    struct tm *tmtoday=NULL, *eachday=calloc(1, sizeof(struct tm));
    char buffer[STRSZ]={0};
    char epsecbf[STRSZ]={0};
    char epsecbf2[STRSZ]={0};

    time( &rawtime );

    tmtoday = localtime( &rawtime );

    /* what's incredible here is how strftime, although it looks like scanf, prtinf and friends
     * is actually very tolerant, as many formatting codes as you like! */
    // strftime(buffer, STRSZ, "%a %x - %I:%M%p", tmtoday);
    strftime(buffer, STRSZ, "%a %d %b %Y in epoch seconds this is %s", tmtoday);
    strftime(epsecbf, STRSZ, "%s", tmtoday);
    long esec = atol(epsecbf);
    int stepday=3600*24;
    long startday=stepday*daysago;
    long j;
    for(j=1427450213;j<esec; j+=stepday)  {
        sprintf(epsecbf2, "%li", j);
        strptime(epsecbf2, "%s", eachday);
        strftime(epsecbf, STRSZ, "%a %d %b %Y", eachday);
        printf("%s\n", epsecbf); 
    }

    printf("---------------\n");
    printf("Formatted date & time string:\n%s\n", buffer);
    printf("Readout No.2 in epochseconds %i\n", tmtoday->tm_sec);
    free(eachday);

    return(0);
}
