/* fastitch.c stitches up fasta files */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h> 

#define GBUF 4
#define MAXVSZ 40
#define MAXISZ 8 // max size of the integer
#define boolean unsigned char

#define CONDREALLOC(x, b, c, a, t); \
    if((x)==(b)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

// following is hard coded for uoa_t and j!
#define CONDREALLOC2(x, b, c, a); \
    if((x)==(b)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(uoa_t)); \
            for(j=(b) - (c); j<(b);++j) { \
                uoa[j].uoibf=(c); \
                uoa[j].uoids=malloc(uoa[j].uoibf*sizeof(int)); \
                uoa[j].uoisz=0; \
            } \
    }

typedef struct /* uoa Unique Occurence Array type: the UO here refers to the length of the sequence: i.e. the occurence of a certain sequnce length. You'll need to remember that :-) . */
{
    unsigned uo; /* the unique occurence this array entry refers to */
    int *uoids; /* the ids of the sequences for this unqiue occurence */
    int uoisz; /* the actual size of the array */
    int uoibf; /* the actual size of the array */
} uoa_t;

int cmpuoabyo(const void *a, const void *b) /* compare uoa by occurence */
{
    uoa_t *ua = (uoa_t*)a; /* cast our void! */
    uoa_t *ub = (uoa_t*)b; /* cast our void! */
    return ua->uo  - ub->uo; /* integer comparison: returns positive if b > a and nagetive if a > b: i.e. highest values first */
}

void prtuoa(uoa_t *uoa, int uoasz)
{
    int i, j;
    for(j=0; j<uoasz;++j) {
        printf("%i: ", uoa[j].uo);
        for(i=0;i<uoa[i].uoisz;++i) 
            printf("%u ", uoa[j].uoids[i]);
        putchar('\n');
    }
}

uoa_t *uniquelens(int *v, int vsz, int *uoasz_)
{
    unsigned char new;
    unsigned i, j;
    unsigned uoabuf=GBUF;
    int uoasz=0;
    uoa_t *uoa=calloc(uoabuf, sizeof(uoa_t));
    for(i=0;i<uoabuf;++i) {
        uoa[i].uoibf=GBUF;
        uoa[i].uoids=malloc(uoa[i].uoibf*sizeof(unsigned));
        uoa[i].uoisz=0;
    }

    for(i=0; i<vsz;++i) {
        new=1;
        for(j=0; j<uoasz;++j) {
            if(uoa[j].uo == v[i]) {
                CONDREALLOC(uoa[j].uoisz, uoa[j].uoibf, GBUF, uoa[j].uoids, unsigned);
                uoa[j].uoids[uoa[j].uoisz] = i;
                uoa[j].uoisz++;
                new=0;
                break;
            }
        }
        if(new) {
            uoasz++;
            CONDREALLOC2(uoasz, uoabuf, GBUF, uoa);
            uoa[uoasz-1].uo = v[i];
            uoa[uoasz-1].uoisz = 1;
            // uoa[uoasz-1].uoids=realloc(uoa[j].uoids, uoa[j].uoisz*sizeof(unsigned));
            uoa[uoasz-1].uoids[uoa[j].uoisz-1] = i;
        }
    }
    for(i=uoasz;i<uoabuf;++i) 
        free(uoa[i].uoids);
    uoa=realloc(uoa, uoasz*sizeof(uoa_t));

    qsort(uoa, uoasz, sizeof(uoa_t), cmpuoabyo);
#ifdef DBG
    printf("number of different sequence lengths: %i\n", uoasz);
    for(j=0; j<uoasz;++j) {
        printf("%i (%u): ", uoa[j].uo, uoa[j].uoisz);
        for(i=0;i<uoa[j].uoisz;++i) 
            printf("%i ", uoa[j].uoids[i]);
        printf("\n"); 
    }
#endif
    *uoasz_ = uoasz;
    return uoa;
}

void prtusage(char *progname)
{
    printf("Help for prog \"%s\":\n", progname);
    printf("Just one arg for the time being\n");
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=1) {
        prtusage(argv[0]);
        exit(EXIT_FAILURE);
    }

    int i, vsz=(int)(MAXVSZ*(float)random()/RAND_MAX);
    int *v=malloc(vsz*sizeof(int));
    for(i=0;i<vsz;++i) 
        v[i] = (int)(MAXISZ*(float)random()/RAND_MAX);

    for(i=0;i<vsz; ++i) 
        printf("%i ", v[i]);
    putchar('\n');

    int uoasz;
    uoa_t *uoc = uniquelens(v, vsz, &uoasz);
    printf("uoasz = %i \n", uoasz); 
    prtuoa(uoc, uoasz);

    for(i=0;i<uoasz;++i)
        free(uoc[i].uoids);
    free(uoc);

    free(v);
    return 0;
}
