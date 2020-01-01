/* where we hard code a 0-5 number sequence to progress row-wise
 * pretty easy as that is the default for printf */
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
    int i, j;
    const int nclines=6;
    const int c=3;

    int r= nclines/c;
    int *arr=malloc(nclines*sizeof(int));
    /* the folloiwn is a counwise progression */
    int k=0;
    for(j=0;j<nclines;++j) {
            arr[j] = j;
    }

    /* original order is */
    printf("Row-wise progression:\n");
    for(i=0;i<nclines;++i) 
        printf("%i ", arr[i]); 
    printf("\n"); 
    k=0;
    printf("Convert to row-wise:\n");
    for(j=0;j<c;++j)
        for(i=0;i<r;++i)
            printf("%i ", arr[j+i*c]); 
    printf("\n"); 

    free(arr);

    return 0;
}
