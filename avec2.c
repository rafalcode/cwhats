/* how to build up an integer vector of arbitrary size 
Note how we use a container for the vector. Sure it involves some extra functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 2
#define CONDREALLOC(x, b, c, a1, a2, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t)); \
        (a2)=realloc((a2), (b)*sizeof(t)); \
        memset(((a2)+(b)-(c)), 0, (c)*sizeof(t)); \
    }

typedef struct /* av_c, holds a vector valeu and a count for it */
{
    int vbf, vsz, *v, *vc;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->v=malloc(avc->vbf*sizeof(int));
    avc->vc=calloc(avc->vbf, sizeof(int));
    avc->vsz=0;
    return avc;
}

void condrea_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, avc->vc, int);
    return;
}

void norm_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    avc->v=realloc(avc->v, avc->vsz*sizeof(int));
    avc->vc=realloc(avc->vc, avc->vsz*sizeof(int));
    return;
}

void free_avc(av_c *avc)
{
    free(avc->v);
    free(avc->vc);
    free(avc);
    return;
}

void coumemb(av_c *avc, int *ia, int iasz)
{

    int i, k;
    unsigned char new;

    for(i=0;i<iasz;++i) {
        new=1;
        for(k=0; k<avc->vsz;++k) {
            if(avc->v[k] == ia[i]) {
                avc->vc[k]++;
                new=0;
                break;
            }
        }
        if(new) {
            condrea_avc(avc);
            avc->v[avc->vsz]=ia[i];
            avc->vc[avc->vsz++]++;
        }
    }

    return;
}

int main(int argc, char *argv[])
{

    int i;

    int *ia= malloc(12*sizeof(int));
    for(i=0;i<12;++i) 
        ia[i]=(int)(4*(float)rand()/RAND_MAX);

    av_c *avc=crea_avc(GBUF);

    coumemb(avc, ia, 12);

    norm_avc(avc);

    printf("Print the random integer vector:\n"); 
    for(i=0;i<12;++i) 
        printf("%i ", ia[i]); 
    printf("\n"); 
    printf("Avec2 printed out:\n"); 
    for(i=0;i<avc->vsz;++i)
        printf("%i/%i ", avc->v[i], avc->vc[i]); 
    printf("\n"); 

    free(ia);
    free_avc(avc);

    return 0;
}
