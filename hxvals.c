#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// printing out  1, 2 or 4 bytevlues in small endian format

#define BC  2 // bit containers

int main(int argc, char *argv[])
{
   int bi=BC*8;
   int h= ((1L<<bi)-1)-(1<<(bi-1));

   printf("Res_1: %x\n", h);

   int i;
   for(i=0;i<BC;++i) 
    printf("%x ", (h>>(i*8))&0xFF);
   printf("\n"); 


   return 0;
}
