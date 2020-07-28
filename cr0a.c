/* where we hard code a 0-5 number sequence to progress columnwise
   but we print it 
   */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int i, j;
    const int nclines=32;
    const int ncols=4;

    int nrows= nclines/ncols;
    int *arr=malloc(nclines*sizeof(int));
    /* the folloiwn is a counwise progression */
    int k=0;
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j) {
            arr[k++] = i*ncols + j;
    }

    /* original order is */
    printf("1D progression is the same in both cases:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr[i]); 
    printf("\n"); 
    printf("Except that, in 2D, column-major looks like so:\n");
    for(j=0;j<nrows;++j) {
        for(i=0;i<ncols;++i)
            printf("%i ", arr[j+i*nrows]); 
        printf("\n"); 
    }
    k=0;
    int *arr2=malloc(nclines*sizeof(int));
    for(j=0;j<nrows;++j)
        for(i=0;i<ncols;++i)
            arr2[j*ncols+i] = arr[j+nrows*i]; 

    printf("So naive mapping to 1D, column-major looks like this:\n"); 
    for(i=0;i<nclines;++i) 
        printf("%i ", arr2[i]); 
    printf("\n"); 
    int *arr3=malloc(nclines*sizeof(int));
    for(i=0;i<nrows;++i)
        for(j=0;j<ncols;++j)
            // arr3[i*ncols+j] = arr2[j*nrows+i]; 
            arr3[j*nrows+i] = arr2[i*ncols+j]; 
    printf("Arr3:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr3[i]); 
    printf("\n"); 

    int ncols2=12;
    int nrows2= nclines/ncols2;
    int lastpr=nclines%ncols2; // last partial row
    printf("How the new array looks ...\n"); 
    for(i=0;i<nrows2;++i) { // 1st D will progress by columns
        for(j=0;j<ncols2;++j) // 2D will progress by rows
            printf("%2i ", arr3[i*ncols2+j]); 
        printf("\n"); 
    }
    for(j=0;j<lastpr;++j) // 2D will progress by rows
        printf("%2i ", arr3[i*ncols2+j]); 
    printf("\n"); 

    free(arr);
    free(arr2);
    free(arr3);

    return 0;
}
