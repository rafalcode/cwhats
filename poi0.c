#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int give(float lambd)
{
    int k=0;
    float L=exp(-lambd), p =1.;
    float ura;
    do {
        k++;
        ura = (float)random()/RAND_MAX;
        p *= ura;
    } while(p>L);
    return k-1;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=3) {
        printf("Error. Pls supply argument (name of file).\n");
        exit(EXIT_FAILURE);
    }
    int i, n=atoi(argv[1]), lambd=atoi(argv[2]);
    int *narr=malloc(n*sizeof(int));
    int k, sum=0;
    for(i=0;i<n;++i) {
        narr[i]=give(lambd);
        sum += narr[i];
        printf("%i ", narr[i]);
    }
    printf("\nAvg=%4.4f\n", (float)sum/n); 
    for(i=0;i<n;++i)
        printf("%4.4f ", 1./narr[i]); 
    printf("\n"); 

    free(narr);

    return 0;
}
