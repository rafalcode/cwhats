/* insertion sort */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETSZ 6

int main(int argc, char *argv[])
{
    int i, j, tmp, A[SETSZ] = {5, 2, 4, 6, 1, 3};

    for(j=0;j<SETSZ;++j)
        printf("%i ", A[j]);
    printf("\n"); 

    for(j=1;j<SETSZ;++j) {

        tmp=A[j];
        i=j-1;
        while( (i>=0) & (A[i] > tmp) ) {
            A[i+1] = A[i];
            /* bug alert .. it's the easiest thign in the world, to hjave the wrong index in that line, i.e.
            A[j+1] = A[j];
            But j is not the free variable in this case, i is. */
            i-=1;
        }
        A[i+1] =tmp;
    }

    for(j=0;j<SETSZ;++j)
        printf("%i ", A[j]);
    printf("\n"); 

    return 0;
}
