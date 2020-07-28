/* where we hard code a 0-5 number sequence to progress row-wise
 * pretty easy as that is the default for printf */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int i, j;
    const int nclines=6;
    const int ncols=3;

    int nrows= nclines/ncols;
    int *arr1=malloc(nclines*sizeof(int));
    int *arr2=malloc(nclines*sizeof(int));
    /* the folloiwn is a counwise progression */
    int k=0;
    for(j=0;j<nclines;++j) {
        arr1[j] = j;
    }

    /* original order is */
    printf("Consecutive progression:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr1[i]); 
    printf("\n"); 
    printf("%ix%i row-wise grid layout:\n", nrows, ncols); 
    for(i=0;i<nrows;++i) {
        for(j=0;j<ncols;++j)
            printf("%i ", arr1[j+i*ncols]); 
        printf("\n"); 
    }
    printf("%ix%i column-wise grid layout:\n", nrows, ncols); 
    for(i=0;i<nrows;++i) {
        for(j=0;j<ncols;++j)
            printf("%i ", arr1[j*nrows+i]); 
        printf("\n"); 
    }

    /* convert */
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            arr2[i*ncols+j] = arr1[j*nrows+i]; 
    printf("After conversion, print straight out:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i ", arr2[j+i*ncols]); 
    printf("\n"); 

    printf("So what's happened? This mapping has occured:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            printf("%i->%i ", arr1[j+i*ncols] , arr2[j+i*ncols]);
    printf("\n"); 

    // k=0;
    // printf("Convert to row-wise:\n");
    // for(j=0;j<ncols;++j)
    //     for(i=0;i<nrows;++i)
    //         arr2[j*nrows+i] = arr1[j+i*ncols]; 
    // for(i=0;i<nclines;++i) 
    //     printf("%i ", arr2[i]); 
    // printf("\n"); 

    // printf("%ix%i grid layout:\n", nrows, ncols); 
    // for(i=0;i<nrows;++i) {
    //     for(j=0;j<ncols;++j)
    //         printf("%i ", arr2[j+i*ncols]); 
    //     printf("\n"); 
    // }

    free(arr1);
    free(arr2);

    return 0;
}
