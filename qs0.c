/* this is a simple use of qsort where the inices are also kept
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct // cartpos
{
	float e; // the elemtn itself
    int i; // index
} el_t;  /* a cartesian position, to lend reality. */

int cmpel(const void *vel1, const void *vel2)
{
    el_t *el1 = (el_t*)vel1;
    el_t *el2 = (el_t*)vel2;

    if(el1->e > el2->e)
        return 1;
    else if(el1->e < el2->e)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{

    int i;
    float d[] ={0.562563577014331,0.55146342532265,0.455946810417661,0.616839222338544,0.510478606387321,0.531118030813163,0.726735806424479,0.664707332811073};
    size_t nd=sizeof(d)/sizeof(float);

    el_t *ed=malloc(nd*sizeof(el_t));
    for(i=0;i<nd;++i) {
        ed[i].e = d[i];
        ed[i].i = i;
    }
    // a second copy to record ranks
    el_t *ed2=malloc(nd*sizeof(el_t));
    for(i=0;i<nd;++i)
        ed2[i].e = d[i];
   
    printf("qs0 is a simple exercise in using qsort to order some fp numbers but also recording where the indices.\n");  
    printf("The hardcoded fp array is %zu in size and consists of:\n", nd);
    for(i=0;i<nd;++i)
        printf("%2.4f ", ed[i].e);
    printf("\n\n"); 

    qsort(ed, nd, sizeof(el_t), cmpel);

    printf("The sorted (qsort) version is as follows:\n");
    for(i=0;i<nd;++i)
        printf("%2.4f ", ed[i].e);
    printf("\n"); 
    for(i=0;i<nd;++i)
        printf("%6i ", ed[i].i);
    printf("\n\n"); 

    printf("Get back original array from just the sorted version is as follows:\n");
    for(i=0;i<nd;++i)
        ed2[ed[i].i].i=i+1;

    printf("And now the original with ranks:\n");
    for(i=0;i<nd;++i)
        printf("%2.4f: Rank %i\n ", ed2[i].e, ed2[i].i);

    free(ed);
    free(ed2);
    return 0;
}
