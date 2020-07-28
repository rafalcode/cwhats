/* merge sort using Fisher ates to create random perm of array. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prtarr(int *arr, int n)
{
    int i;
    for(i=0;i<n;++i)
        printf("%i ", arr[i]);
    printf("\n"); 
    return;
}

void initarr(int *arr, int n)
{
    int i;
    for(i=0;i<n;++i)
        arr[i]=i;

    return;
}

void fy(int *arr, int n)
{
    int i, j, tmp, r;

    for(i=n-1;i>=0;--i) {
        r=rand()%(i+1);
        tmp=arr[r];
        arr[r] = arr[i];
        arr[i]=tmp;
    }

    return;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls supply argument (integer).\n");
        exit(EXIT_FAILURE);
    }
    int n=atoi(argv[1]);
    int *arr=malloc(n*sizeof(int));

    initarr(arr, n);
    fy(arr, n);
    prtarr(arr, n);

    int i, j, tmp;
    int neven=n&0xFFFFFFFE;
    for(i=0;i<neven;i+=2) 
        if(arr[i]>arr[i+1]) {
            tmp=arr[i]; arr[i]=arr[i+1]; arr[i+1]=tmp;
        }

    prtarr(arr, n);










    free(arr);
    return 0;
}
