/* fastitch.c stitches up fasta files */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <dirent.h> 

#define GBUF 2
#define MAXVSZ 16
#define MAXISZ 5 // max size of the integer
#define boolean unsigned char

#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

// following is hard coded for uoa_t and it has its own iterative index, k9 for fun and uniqueness.
#define CONDREALLOC2(x, b, c, a); \
    int k9; \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(uoa_t)); \
            for(k9=(b) - (c); k9<(b);++k9) { \
                uoa[k9].uoibf=(c); \
                uoa[k9].uoids=malloc(uoa[k9].uoibf*sizeof(int)); \
                uoa[k9].uoisz=0; \
                uoa[k9].uo=-1; \
            } \
    }

typedef struct /* uoa Unique Occurence Array type: the UO here refers to the length of the sequence: i.e. the occurence of a certain sequnce length. You'll need to remember that :-) . */
{
    int uo; /* the unique occurence this array entry refers to */
    int *uoids; /* the indices corresponding to the uo unique occurence. */
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
        printf("val %i (sz=%i): ", uoa[j].uo, uoa[j].uoisz);
        for(i=0;i<uoa[j].uoisz;++i) 
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
    uoa_t *uoa=malloc(uoabuf*sizeof(uoa_t));
    for(i=0;i<uoabuf;++i) {
        uoa[i].uoibf=GBUF;
        uoa[i].uoids=malloc(uoa[i].uoibf*sizeof(int));
        uoa[i].uoisz=0;
        uoa[i].uo=-1; // intialiazed, albeit to an invlid index type.
    }

    for(i=0; i<vsz;++i) {
        new=1;
        for(j=0; j<uoasz;++j) {
            if(uoa[j].uo == v[i]) {
                CONDREALLOC(uoa[j].uoisz, uoa[j].uoibf, GBUF, uoa[j].uoids, int);
#ifdef DBG
                printf("APPENDING uoaind %i (ou=%i) @sz %i @buf %i adding vind %i\n", j, v[i], uoa[j].uoisz, uoa[j].uoibf, i);
#endif
                uoa[j].uoids[uoa[j].uoisz] = i;
                uoa[j].uoisz++;
                new=0;
                break;
            }
        }
        if(new) {
            uoasz++;
            CONDREALLOC2(uoasz, uoabuf, GBUF, uoa);
#ifdef DBG
                printf("NEW uoaind %i (ou=%i) @sz %i @buf %i adding vind %i\n", j, v[i], uoa[j].uoisz, uoa[j].uoibf, i);
#endif
            uoa[uoasz-1].uo = v[i];
            uoa[uoasz-1].uoisz++;
            uoa[uoasz-1].uoids[uoa[j].uoisz-1] = i;
            // uoa[uoasz-1].uoids=realloc(uoa[j].uoids, uoa[j].uoisz*sizeof(unsigned));
        }
    }

    // normalizing
    for(i=uoasz;i<uoabuf;++i) {
        free(uoa[i].uoids);
        // free(uoa[i]);
    }
    uoa=realloc(uoa, uoasz*sizeof(uoa_t));

    // qsort(uoa, uoasz, sizeof(uoa_t), cmpuoabyo);
#ifdef DBG
    printf("number of different values: %i\n", uoasz);
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
    int i;

    int vsz=(int)(MAXVSZ*(float)random()/RAND_MAX); // what will be the size of our integer vector (up to a certain max)?
    int *v=malloc(vsz*sizeof(int));
    for(i=0;i<vsz;++i) 
        v[i] = (int)(MAXISZ*(float)random()/RAND_MAX); // each element a random integer (up to a certain max).

    // let's see what we got:
    printf("Indices: "); 
    for(i=0;i<vsz; ++i) 
        printf("%3i ", i);
    putchar('\n');
    printf(" Values: "); 
    for(i=0;i<vsz; ++i) 
        printf("%3i ", v[i]);
    putchar('\n');

    int uoasz;
    uoa_t *uoa = uniquelens(v, vsz, &uoasz);
    printf("uoasz = %i \n", uoasz); 
    prtuoa(uoa, uoasz);

    for(i=0;i<uoasz;++i)
        free(uoa[i].uoids);
    free(uoa);

    free(v);
    return 0;
}
