/* how to build up an integer vector of arbitrary size 
Note how we use a container for the vector. Sure, it involves some extra functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOCMN(x, b, c, m, n, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (m)=realloc((m), (b)*sizeof(t)); \
        (n)=realloc((n), (b)*sizeof(t)); \
    }

typedef struct /* av_c, a vector fo simple integers*/
{
    int vbf, vsz, *m, *n;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->m=malloc(avc->vbf*sizeof(int));
    avc->n=malloc(avc->vbf*sizeof(int));
    avc->vsz=0;
    return avc;
}

void app_avc(av_c *avc, int m, int n)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOCMN(avc->vsz, avc->vbf, GBUF, avc->m, avc->n, int);
    avc->m[avc->vsz]=m;
    avc->n[avc->vsz++]=n;
    return;
}

void memexact_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    avc->m=realloc(avc->m, avc->vsz*sizeof(int));
    avc->n=realloc(avc->n, avc->vsz*sizeof(int));
    return;
}

void free_avc(av_c *avc)
{
    free(avc->m);
    free(avc->n);
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
	char *tk0=strtok(argv[1], t);
	if(tk0 ==NULL) {
		printf("First strtok returned NULL\n"); 
	    exit(EXIT_FAILURE);
    }
    av_c *avc=crea_avc(GBUF);
    avc->m[avc->vsz]=atoi(tk0);
	char *tk2=strtok(NULL, t);
    app_avc(avc, atoi(tk0), atoi(tk2));
	while( ((tk0=strtok(NULL, t)) != NULL) & ( (tk2=strtok(NULL, t)) != NULL))
        app_avc(avc, atoi(tk0), atoi(tk2));

    printf("Avec printed out:\n"); 
    for(i=0;i<avc->vsz;++i)
        printf("(%i,%i) ", avc->m[i], avc->n[i]);
    printf("\n"); 

    memexact_avc(avc);
    free_avc(avc);

    return 0;
}
