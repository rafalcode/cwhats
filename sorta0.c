/* aownsa.c array owns another in various ways */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define SETSEED 0 // note 300th element on arr2 is actually 1.000 in this run!
#define LIMTYPESZ 10

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
    srandom(SETSEED);

    int i, n=12;
    int *arr1=malloc(n*sizeof(int));
    for(i=0;i<n;++i) arr1[i]=1000*(float)random()/RAND_MAX;
    for(i=0;i<n;++i) printf("%4i ", arr1[i]);
    printf("\n"); 

    qsort(arr1, n, sizeof(float), cmpflo);

    free(arr1);

    return 0;
}
