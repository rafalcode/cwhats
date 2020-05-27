/* where we hard code a 0-5 number sequence to progress columnwise
   but we print it 
   */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int i, j;
    const int nclines=6;
    const int ncols=3;

    int nrows= nclines/ncols;
    int *arr=malloc(nclines*sizeof(int));
    /* the folloiwn is a counwise progression */
    int k=0;
    for(j=0;j<ncols;++j) {
        for(i=0;i<nrows;++i)
            arr[k++] = j+ncols*i;
    }

    /* original order is */
    printf("Column-wise progression:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr[i]); 
    printf("\n"); 
    printf("Or in grid layout:\n"); 
    for(i=0;i<ncols;++i) {
        for(j=0;j<nrows;++j)
            printf("%i ", arr[j+i*nrows]); 
        printf("\n"); 
    }
    k=0;
    printf("Convert to row-wise:\n");
    for(i=0;i<nrows;++i) {
        for(j=0;j<ncols;++j)
            printf("%i ", arr[i+j*nrows]); 
        printf("\n"); 
    }

    free(arr);

    return 0;
}
