/* aownsa.c array owns another in various ways */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define SETSEED 0 // note 300th element on arr2 is actually 1.000 in this run!
#define LIMTYPESZ 10

typedef struct  /* optstruct, a struct for the options */
{
    int rflag; /* for unredictable random numbers */
    int nflag; /* only print number of children elements */
} optstruct;

int catchopts(optstruct *opstru, int oargc, char **oargv)
{
    int c;
    opterr = 0;
    while ((c = getopt(oargc, oargv, "rn")) != -1)
        switch (c) {
            case 'r':
                opstru->rflag = 1;
                break;
            case 'n':
                opstru->nflag = 1;
                break;
            default:
                abort();
        }
    return 0;
}

int cmpflo(const void *flo1, const void *flo2)
{
    float *f1 = (float*)flo1;
    float *f2 = (float*)flo2;

    if(*f1>*f2)
        return 1;
    else if(*f1<*f2)
        return -1;
    else
        return 0;
}

float uplim01(float *arr1, int idx, int sz, char *limtype) // upper limit
{
    /* upper limit of a certain index's ownership
     * this function only useful if called from a loop
     * which progress up from 0 to 1 real number line
    */
    float ret;

    if(idx==sz-1)
        ret=1.;
        // ret=arr1[sz-1];
    else if( !strcmp("pt_as_mid", limtype) )
        ret=arr1[idx]+(arr1[idx+1]-arr1[idx])/2.;
    else if( !strcmp("pt_as_spl", limtype) )
        ret=arr1[idx];

    return ret;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if((argc<4) | (argc>5)) {
        printf("Proper usage: Pls supply numb floats in first array, then numb floats in second array\n");
        printf("In third place the output file name.\n");
        printf("You can optionally follow these values with an -r flag to generate different pseudorandom values.\n");
        exit(EXIT_FAILURE);
    }
    optstruct opstru={0};
    int argignore=3; //
    int oargc=argc-argignore;
    char **oargv=argv+argignore;

    /* OK< do we have an -r flag? */
    struct timeval tnow;
    unsigned tseed;
    catchopts(&opstru, oargc, oargv);
    if(opstru.rflag) {
        gettimeofday(&tnow, NULL);
        /*  use the five last digits of the current microsecond reading to generate a seed */
        tseed=(unsigned int)((tnow.tv_usec/100000.0 - tnow.tv_usec/100000)*RAND_MAX);
#ifdef DBG
        printf("ts=%7.5f\n", (tnow.tv_usec/100000.0 - tnow.tv_usec/100000));
        printf("RAND_MAX: %u\n", RAND_MAX); 
        printf("time-seed came out as: %u\n", tseed); 
#endif
        srandom(tseed);
    } else
        srandom(SETSEED);

    int i, n=atoi(argv[1]), m=atoi(argv[2]);
    float *arr1=malloc(n*sizeof(float)), *arr2=malloc(m*sizeof(float));

    for(i=0;i<n;++i) arr1[i]=(float)random()/RAND_MAX;
    qsort(arr1, n, sizeof(float), cmpflo);

    for(i=0;i<m;++i) arr2[i]=(float)random()/RAND_MAX;
    qsort(arr2, m, sizeof(float), cmpflo);

    FILE *fop=fopen(argv[3], "w");
    for(i=0;i<n;++i) 
        fprintf(fop, "%4.4f\n", arr1[i]);
    fprintf(fop, "\n");
    for(i=0;i<m;++i) 
        fprintf(fop, "%4.4f\n", arr2[i]);
    fclose(fop);

    free(arr1);
    free(arr2);

    return 0;
}
