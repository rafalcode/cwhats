/* takes 6 digits and assumes it's a time, and will output epoch seconds
 * this is usefull for getting linear differences between times without worrying about the sexigesimals suchas mins and secs.
 */
#define _GNU_SOURCE // actually needed for getline 
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<sys/stat.h>

#define THROWAWAYMEMSZ 128
#define GBUF 4
#define CONDREALLOC(x, b, c, a, t, a2, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        for(i=((b)-(c));i<(b);++i) { \
            ((a)[i]) = NULL; \
            ((a2)[i]) = 0; \
        } \
    }

typedef struct /* larr_t line array struct */
{
    char **l;
    size_t *lz;
    int lbf;
    int asz;
} larr_t;

larr_t *slurplines(char *fn)
{
    FILE *stream;
    // char *line = NULL;
    size_t len = 0;
    int i;

    stream = fopen(fn, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    larr_t *la=malloc(sizeof(larr_t));
    la->lbf=GBUF;
    la->asz=0;
    la->l=malloc(la->lbf*sizeof(char*)); // does need this, yes, though later it won't be free'd
    la->lz=malloc(la->lbf*sizeof(size_t)); // does need this, yes, though later it won't be free'd
    for(i=0;i<la->lbf;++i) {
        la->lz[i]=0;
        la->l[i]=NULL;
    }

    while ((la->lz[la->asz] = getline(la->l+la->asz, &len, stream)) != -1) {
        // nread is number of returned characters
        CONDREALLOC(la->asz, la->lbf, GBUF, la->l, char*, la->lz, size_t);
        // printf("Retrieved line of length (returned val method): %zu\n", nread);
        // printf("Retrieved line of length (strlen method): %zu\n", strlen(line));
        // fwrite(line, nread, 1, stdout);
        if(la->l[la->asz][la->lz[la->asz]-1]=='\n') // check the newline
            la->l[la->asz][la->lz[la->asz]-1]='\0'; // smash the newline, of course you could save a byte and reallocate, etc. etc.
        la->asz++;
    }

    /* now to see if normalise works */
    for(i=la->asz;i<la->lbf;++i)
        free(la->l[i]);
    la->l=realloc(la->l, la->asz*sizeof(char*)); // normalize
    la->lz=realloc(la->lz, la->asz*sizeof(size_t)); // normalize

    /* Ok that's it */
    fclose(stream);
    return la;
}

int main (int argc, char *argv[])
{

    // struct tm *mtime = localtime(&ifsta.st_mtime);
    // what is struct tm?
    //int    tm_sec   seconds [0,61]
    //int    tm_min   minutes [0,59]
    //int    tm_hour  hour [0,23]

    if(argc!=2)  {
        printf("One arg required: filename six digit continuous timespecs per line\n");
        exit(EXIT_FAILURE);
    }
    larr_t *la=slurplines(argv[1]);
    printf("how many timespec lines? i.e. asz :%i\n", la->asz); 
    long long *secarray=calloc(la->asz, sizeof(long long)); 

    int i;
    // sscanf(anytime, "%2d%2d%2d", &h, &m , &s);
    struct tm *tm_var=calloc(1, sizeof(struct tm));
    // the following are fillers, 01/01/1970 is a standard date, makes everything paly blla
    tm_var->tm_mday=1;
    // tm_var->tm_mon=0; // not necessary because of the calloc
    tm_var->tm_year=70;
    char *mtime_str=calloc(THROWAWAYMEMSZ, sizeof(char));

    for(i=0;i<la->asz;++i) {
        // here we get the timespec string and convert it to struct tm
        sscanf(la->l[i], "%2d%2d%2d", &tm_var->tm_hour, &tm_var->tm_min, &tm_var->tm_sec);
        // if there were tokens between the components such as 14:22:33 the 2 in %2d would not be necessary
        // as in:
        // sscanf(anytime, "%d:%d:%d", &tm_var.tm_hour, &tm_var.tm_min, &tm_var.tm_sec);


        if (strftime(mtime_str, THROWAWAYMEMSZ, "%s", tm_var) == 0) {
            fprintf(stderr, "strftime returned 0");
            exit(EXIT_FAILURE);
        }

        secarray[i]=atol(mtime_str);
    }


    for(i=1;i<la->asz;++i) {
        printf("%lli\n", secarray[i]); 
        if(secarray[i] < secarray[i-1])
            printf("Not monitonically increasingi entry found at idx %i\n", i); 
        else if(secarray[i] == secarray[i-1])
            printf("Repeat second entry found at idx %i\n", i); 
    }
    printf("endtime-startime=%lli\n", secarray[la->asz-1] - secarray[0]); 

    for(i=0;i<la->asz;++i)
        free(la->l[i]);
    free(la->l);
    free(la->lz);
    free(la);
    free(tm_var);
    free(mtime_str);
    free(secarray);
    return 0;
}
