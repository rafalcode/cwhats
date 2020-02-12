/* insertion sort */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETSZ 6

void inssortia(int *a, int n)
{
    int i, j;
    int tmp;
    for(i=1; i<n; i++) {
        tmp=a[i];
        j = i-1;
        while(tmp < a[j] && j>=0) {
            a[j+1]=a[j];
            j -= 1;
        }   
        a[j+1] = tmp;
    }   
}

int main(int argc, char *argv[])
{
   int j, A[SETSZ] = {5, 2, 4, 6, 1, 3};

   for(j=0;j<SETSZ;++j)
       printf("%i ", A[j]);
   printf("\n"); 
   inssortia(A, SETSZ);
   for(j=0;j<SETSZ;++j)
       printf("%i ", A[j]);
   printf("\n"); 
   return 0;
}
