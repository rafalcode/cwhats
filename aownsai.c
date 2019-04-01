/* aownsa.c array owns another in various ways */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define SETSEED 0 // note 300th element on arr2 is actually 1.000 in this run!

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

int cmpll(const void *ll1_, const void *ll2_)
{
    long *ll1 = (long*)ll1_;
    long *ll2 = (long*)ll2_;

    if(*ll1>*ll2)
        return 1;
    else if(*ll1<*ll2)
        return -1;
    else
        return 0;
}

long uplim(long *arr1, int idx, int sz, long dynmx) // upper limit
{
    /* upper limit of a certain index's ownership
     * this function only useful if called from a loop
     * which progress up from 0 to 1 real number line
    */
    long ret;

    if(idx==sz-1)
        ret=dynmx;
    else
        ret=arr1[idx]+ceil((float)(arr1[idx+1]-arr1[idx])/2.);
    /* note above how if 3 and and next element 7 fight over 5, it is assigned to 3. */

    return ret;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if((argc<4) | (argc>6)) {
        printf("Proper usage: Pls supply numb nodes in owning array, then numb nodes in belonging array\n");
        printf("              Also dynamic maximum is required as third (free) argument.\n");
        printf("              You can optionally follow these values with an -r flag to generate different pseudorandom values.\n");
        printf("              An -n option is also available to only see number of children to each parent. It also gives a summary.\n");
        exit(EXIT_FAILURE);
    }
    optstruct opstru={0};
    int argignore=3;
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

    int i, j, n=atoi(argv[1]), m=atoi(argv[2]), dynmx=atol(argv[3]);

    long *arr1=malloc(n*sizeof(long)), *arr2=malloc(m*sizeof(long));
    int *oarr1=malloc(n*sizeof(int));
    memset(oarr1, -1, n*sizeof(int)); // if -1 then zero ownership for that index of arr1

    for(i=0;i<n;++i) arr1[i]=(long)(dynmx*(float)random()/RAND_MAX);
    for(i=0;i<m;++i) arr2[i]=(long)(dynmx*(float)random()/RAND_MAX);

    /* sorem! */
    qsort(arr1, n, sizeof(long), cmpll);
    qsort(arr2, m, sizeof(long), cmpll);

#ifdef DBG
    printf("This is owning array in increasing order\n"); 
    for(i=0;i<n;++i) printf("%li ", arr1[i]);
    printf("\n"); 
    printf("This is belonging array in increasing order\n"); 
    for(i=0;i<m;++i) printf("%li ", arr2[i]);
#endif

    long ulim;
    int k=0, k2=0;
    for(k=0;k<n;k++) {
        ulim= uplim(arr1, k, n, dynmx);
        while(arr2[k2] <= ulim) {
            oarr1[k] = k2;
#ifdef DBG
            printf("is %li less than %li? ... ", arr2[k2], uplim(arr1, k, n, dynmx)); 
#endif
            k2++;
            if(k2==m)break;
        }
#ifdef DBG
        printf("\n"); 
#endif
    }

#ifdef DBG
    //checkout oarr1
    for(i=0;i<n;++i)
        printf("%i ", oarr1[i]); 
    printf("\n"); 
#endif

    int lastgoodidx; // needed because we're using -1 as the index value for a arr1 eleemtn that owns no arr2's.
    int sum=0;
    int nparents=0;

    // printf("Elements of first parent array, each with its list of elements in child array which they \"own\":\n\n");
    printf("Parent array is as follows:\n");
    for(i=0;i<n;++i) 
        printf("%li ", arr1[i]);
    printf("\nChild array is as follows:\n");
    for(i=0;i<m;++i) 
        printf("%li ", arr2[i]);
    putchar('\n');
    putchar('\n');
    printf("Ownership calculation:\n"); 

    // first element
    if(!opstru.nflag) {
        if(oarr1[0] != -1)
            printf("%li: ", arr1[0]);
        for(j=0;j<=oarr1[0];++j)
            printf((j!=oarr1[0])?"%li ":"%li\n", arr2[j]); 
    } else {
        // printf((oarr1[0]==-1)?"0":"%i\n", arr1[0]+1); // incredibly, it will be zero if -1
        printf("%li: ", arr1[0]);
        printf("%i\n", oarr1[0]+1); 
        sum += oarr1[0]+1; 
        nparents++;
    }

    for(i=1;i<n;++i) {
        if(oarr1[i-1] != -1)
            lastgoodidx = oarr1[i-1]+1;
        if(!opstru.nflag) {
            if(oarr1[i] != -1)
                printf("%li: ", arr1[i]); // to avoid verbosity do no print elements with no children.
            if(oarr1[i] == -1)
                continue;

            for(j=lastgoodidx;j<=oarr1[i];++j) 
                printf((j!=oarr1[i])?"%li ":"%li\n", arr2[j]); 

        } else {
            printf("%li: ", arr1[i]); // all parent elements will be printed with nflag.
            printf("%i\n", oarr1[i]+1-lastgoodidx);
            sum += oarr1[i]+1-lastgoodidx;
            nparents++;
        }
    }
    if(opstru.nflag)
        printf("Summary %i child elements owned by %i elements of the %i-sized parent array\n", sum, nparents, n); 

    free(arr1);
    free(oarr1);
    free(arr2);

    return 0;
}
