/* aownsa.c array owns another in various ways */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int cmpflo(const void *flo1, const void *flo2)
{
    float *f1 = (float*)flo1;
    float *f2 = (float*)flo2;

    if(*f1>*f2)
        return 1;
    else if(*f1<*f2)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=3) {
        printf("Error. Pls supply numb nodes in owning array, then numb nodes in belonging array\n");
        exit(EXIT_FAILURE);
    }
    int i, j, n=atoi(argv[1]), m=atoi(argv[2]);

    float *arr1=malloc(n*sizeof(float)), *arr2=malloc(m*sizeof(float));
    int *oarr1=calloc(n, sizeof(int));

    for(i=0;i<n;++i) arr1[i]=(float)random()/RAND_MAX;
    for(i=0;i<m;++i) arr2[i]=(float)random()/RAND_MAX;

    /* sorem! */
    qsort(arr1, n, sizeof(float), cmpflo);
    qsort(arr2, m, sizeof(float), cmpflo);

    for(i=0;i<n;++i) printf("%4.4f ", arr1[i]);
    printf("\n"); 
    for(i=0;i<m;++i) printf("%4.4f ", arr2[i]);
    printf("\n"); 

    int k=0, k2=0;
    while(k2 < m) {
        while(arr2[k2] < arr1[k]) {
            oarr1[k] = k2;
            k2++;
        }
        k++;
        if(k>=n)break;
    }

    for(i=0;i<n;++i) {
        for(j=0;j<oarr1[i];++j) 
            printf("%4.4f ", arr2[j]); 
        printf("\n"); 
    }

    free(arr1);
    free(oarr1);
    free(arr2);

    return 0;
}
