/* how to build up an integer vector of arbitrary size 
Note how we use a container for the vector. Sure it involves some extra functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

typedef struct
{
    int vbf, vsz, *v;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->v=malloc(avc->vbf*sizeof(int));
    avc->vsz=0;
    return avc;
}

void condrea_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, int);
    return;
}

void norm_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    avc->v=realloc(avc->v, avc->vsz*sizeof(int));
    return;
}

void free_avc(av_c *avc)
{
    free(avc->v);
    free(avc);
    return;
}

void prtavec(av_c *avc)
{
    int i;
    printf("Printing elements of vector of size %i:\n", avc->vsz); 
    for(i=0;i<avc->vsz;++i)
        printf("%i ", avc->v[i]); 
    printf("\n"); 

    return;
}

void prtavecdbg(av_c *avc)
{
    int i;
    for(i=0;i<avc->vsz;++i)
        printf("%i ", avc->v[i]); 
    printf("\n"); 

    return;
}

void shufflevec(av_c *avc)
{
    int i;

    int r, ti;
    float rf;
    for(i=avc->vsz-1;i>=0;--i) {
        rf=(float)rand()/RAND_MAX;
        r=(int)((i+1)*rf);
#ifdef DBG
        printf("%i:%4.4f:%i: ", i, rf, r); 
#endif
        prtavecdbg(avc);
        ti=avc->v[i];
        avc->v[i]=avc->v[r];
        avc->v[r] = ti;
#ifdef DBG
        prtavecdbg(avc);
#endif
    }

    return;
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        printf("2 args pls: 1) sz of array 2) rand seed\n");
        exit(EXIT_FAILURE);
    }
    int sz=atoi(argv[1]);
    srand(atoi(argv[2]));
    av_c *avc=crea_avc(GBUF);


    int i;

    for(i=0;i<sz;++i) {
        condrea_avc(avc);
        avc->v[avc->vsz++]=i;
    }
    norm_avc(avc);

#ifndef DBG
    prtavec(avc);
#endif

    shufflevec(avc);

#ifndef DBG
    prtavec(avc);
#endif

    free_avc(avc);

    return 0;
}
