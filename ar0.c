#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GSZ 4


/* quick program to show how memset can be used on a non-dynamic array.
 * Also shows how setting to zero seems to have a short cut on when
 * declaring an nondynamic array for the first time. */
int main(int argc, char *argv[])
{

    int i;
   /* declarations */
   int ar[GSZ]={0};
   ar[1]=9;
   // ar[GSZ]={0};
   memset(ar, 0, GSZ*sizeof(int));
   for(i=0;i<GSZ;++i) 
       printf("%d ", ar[i]); 
   printf("\n"); 

   return 0;
}
