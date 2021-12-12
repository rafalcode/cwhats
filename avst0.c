/* how to build up an integer vector of arbitrary size 
Note how we use a container for the vector. Sure, it involves some extra functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

typedef struct /* av_c, a vector fo simple integers*/
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

void app_avc(av_c *avc, int myint)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, int);
    avc->v[avc->vsz++]=myint;
    return;
}

void memexact_avc(av_c *avc)
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

int main(int argc, char *argv[])
{
    if(argc!=2) {
        printf("%s, an implementation of a stack, using a container array. Requires a comma-separated string of integers\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int i;
	char t[]=",";
	char *tk=strtok(argv[1], t);
	if(tk ==NULL) {
		printf("First strtok returned NULL\n"); 
	    exit(EXIT_FAILURE);
    }
    av_c *avc=crea_avc(GBUF);
    avc->v[avc->vsz++]=atoi(tk);
	while( (tk=strtok(NULL, t)) != NULL)
        app_avc(avc, atoi(tk));

    printf("Avec printed out:\n"); 
    for(i=0;i<avc->vsz;++i)
        printf("%i ", avc->v[i]); 
    printf("\n"); 

    memexact_avc(avc);
    free_avc(avc);

    return 0;
}
