/* insertion sort */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SETSZ 6

int main(int argc, char *argv[])
{
   int i, j, key, A[SETSZ] = {5, 2, 4, 6, 1, 3};

   for(j=1;j<SETSZ;++j) {

       key=A[j];
        i=j-1;
        while( (i>=0) & (A[j] > key) ) {
            A[j+1] = A[j];
            i=i-1;
        }
        A[i+1] =key;
   }

   for(j=0;j<SETSZ;++j)
       printf("%i ", A[j]);
   printf("\n"); 

   return 0;
}
