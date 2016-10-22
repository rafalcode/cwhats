/* picking single shorts from mapping numbers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRINT 0 // select the first int of the pair from which to grab the last two chars. Set to 0 for second int

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls supply argument (integer).\n");
        exit(EXIT_FAILURE);
    }

    int n=atoi(argv[1]);
    if( n%8 ) {
        printf("Error. N should be a multiple of 8, that's the nature of the exercise.\n");
        exit(EXIT_FAILURE);
    }

    int *nbf=malloc((n/4)*sizeof(int));
    // int *nbf=malloc(n*sizeof(int));
    int i, ii, j, jj, k;

    /*
    if(FIRINT) {
        nbf[0]=2;
        nbf[1]=3;
    } else {
        nbf[0]=3;
        nbf[1]=4;
    }
    */

    int firstbyte;
    if(FIRINT)
        firstbyte=2;
    else
        firstbyte=6;

    ii=0;
    for(i=firstbyte;i<n;i+=2) {
        k=(i-firstbyte)%8;
        if(!k) {
            nbf[ii]=i;
            nbf[ii+1]=i+1;
            ii+=2;
        }
    }
    for(i=0;i<n/4;++i) 
        printf("%d=%d ", i, nbf[i]);
    printf("\n"); 

    free(nbf);
    return 0;
}
