#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 16
#define N2 32
int main(int argc, char *argv[])
{

   int i;
   printf("SImple dual channel 32 to 16 conv:\n"); 
   for(i=0;i<N;i+=2) {
       printf("%i:%i ", i, 2*i+2);
       printf("%i:%i ", i+1, 2*i+3);
   }
   printf("\n32 to 16bit and Monoize on first channel:\n"); 
   for(i=0;i<N;i+=2) {
       printf("%i:%i ", i, 4*i+4);
       printf("%i:%i ", i+1, 4*i+5);
   }
   printf("\n32 to 16bit and Monoize on second channel:\n"); 
   for(i=0;i<N;i+=2) {
       printf("%i:%i ", i, 4*i+6);
       printf("%i:%i ", i+1, 4*i+7);
   }
    printf("\n"); 
   for(i=0;i<N;i++)
       printf("%i:%i ", i, (i/4)%2);
    printf("\n"); 
   return 0;
}
