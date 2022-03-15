/* like avec and avsta but just an expanding string that's all */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOCW(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

typedef struct /* av_c, a vector fo simple integers*/
{
    int vbf, vsz;
    char *v;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->v=malloc(avc->vbf*sizeof(char));
    avc->vsz=0;
    return avc;
}

void app_avc(av_c *avc, char mychar)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, char);
    avc->v[avc->vsz++]=mychar;
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
    int i, k=0;
	char c;
    av_c *avc=crea_avc(GBUF);
	while( (c=argv[1][k++]) !='\0')
        app_avc(avc, c);

    printf("Avec printed out:\n"); 
    for(i=0;i<avc->vsz;++i)
        putchar(avc->v[i]); 
    printf("\n"); 

    memexact_avc(avc);
    free_avc(avc);

    return 0;
}
