/* let's now take a known table of values and lead of a vector off of it */
/* note this is limited in that we must know the total number of different integer values
 *
 * juegooca, the occurrences program is better if you don't know that */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

typedef struct /* av_c */
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

int *rendrv(int maxisz, int vsz)
{
    int i, *v=malloc(vsz*sizeof(int));
    for(i=0;i<vsz;++i) 
        v[i] = (int)(maxisz*(float)rand()/RAND_MAX); // each element a random integer (up to a certain max).
    return v;
}

int main(int argc, char *argv[])
{
	if(argc!=3) {
		printf("tabvec: A simple integer table vector program.\n");
		printf("usage:  Two args required: 1) how many different integer values? 2) size of the randomly generated vector of those different integers, with repeats quite obviously.\n");
		exit(EXIT_FAILURE);
	}
    int i, j;
    int maxisz /* max integer size */ = atoi(argv[1]);
    int vsz /* rand vect size */ = atoi(argv[2]);
    int *v=rendrv(maxisz, vsz);
    printf("OK, with those inputs, here's the random vector that will be the subject of our analysis:\n"); 
    for(i=0;i<vsz;++i) 
        printf("%i ", v[i]);
    printf("\n"); 

    av_c **avc=malloc(maxisz*sizeof(av_c*));
    for(i=0;i<maxisz;++i) 
        avc[i]=crea_avc(GBUF);

    for(i=0;i<vsz;++i)
        for(j=0;j<maxisz;++j)
            if(v[i]==j) {
                CONDREALLOC(avc[j]->vsz, avc[j]->vbf, GBUF, avc[j]->v, int);
                avc[j]->v[avc[j]->vsz++]=i;
                break;
            }

    for(i=0;i<maxisz;++i) 
        norm_avc(avc[j]);

    printf("Avec printed out:\n"); 
    for(i=0;i<maxisz;++i) {
        printf("%i(%i): ", i, avc[i]->vsz); 
        for(j=0;j<avc[i]->vsz;++j) 
            printf("%i ", avc[i]->v[j]); 
        printf("\n"); 
    }

    for(i=0;i<maxisz;++i) 
        free_avc(avc[i]);
    free(avc);
    free(v);

    return 0;
}
