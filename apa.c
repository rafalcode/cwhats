#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 2
#define MAXTAB 5
#define MAXCPT 10 // max customers per table
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }
#define CONDREALLOC2(x, b, c, a1, a2, t1, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
    }
#define CONDREALLOC3(x, b, c, a1, a2, a3, t1, t2, t3); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        (a3)=realloc((a3), (b)*sizeof(t3)); \
    }

int main(int argc, char *argv[])
{
    int i;
    int asz=12;
    int *a=calloc(asz, sizeof(int));
    int **ap=malloc(asz*sizeof(int*));
    for(i=0;i<asz;++i) {
        a[i]=(i+1)*3;
        ap[i] = a+i;
    }


    for(i=0;i<asz;++i)
        printf("%i ", *ap[i]); 
    printf("\n"); 

    free(ap);
    free(a);

    return 0;
}
