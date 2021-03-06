/* let's now take a known table of values and lead of a vector off of it */
/* this is actaully an attempt at doing a merge sort */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

void prtv(int *v, int vsz)
{
    int i;
    printf("New ord:\n"); 
    for(i=0;i<vsz;++i) 
        printf("%i ", v[i]);
    printf("\n"); 
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
	if(argc!=2) {
		printf("mergeatt: A simple integer table vector program.\n");
		printf("One arg: random number seed.\n");
		exit(EXIT_FAILURE);
	}
    srand(atoi(argv[1]));
    int i, j, k;
    int maxisz =100;
    int vsz =16;
    int *v=rendrv(maxisz, vsz);
    printf("Here's the random vector:\n"); 
    for(i=0;i<vsz;++i) 
        printf("%i ", v[i]);
    printf("\n"); 
    // int r=1;
    // i=1;
//    while(r<=vsz)
//        for(j=0;j<r;++j) 
//            printf("%i %i", 
//        // printf("%i\n", r<<=i++); 
//        printf("%i\n", r<<=i++); 
    int tmp, j0, j2, m;
    for(j=0;j<vsz;j+=2) {
        j2=j+1;
        if(v[j]>v[j2]) {
            tmp=v[j2]; v[j2]=v[j], v[j]=tmp; //swap!
        }
    }

    for(j=0;j<vsz;j+=4) {
        for(k=0;k<2;k++) {
            j0=j+k;
            j2=j+k+2;
            printf("%i,%i \n", j0, j2); 
            if(v[j0]>v[j2]) {
                tmp=v[j2]; v[j2]=v[j0], v[j0]=tmp; //swap!
            }
        }
    }
    prtv(v, vsz);
    for(j=0;j<vsz;j+=8) {
        k=0;
        m=0;
        while((k<4) | (m<4)) {
            j0=j+m;
            j2=j+k+4;
            printf("%i,%i \n", j0, j2); 
            if(v[j0]>v[j2]) {
                tmp=v[j2]; v[j2]=v[j0], v[j0]=tmp; //swap!
            } else {
                m++;
                continue;
            }
            k++;
        }
    }
    prtv(v, vsz);
    free(v);

    return 0;
}
