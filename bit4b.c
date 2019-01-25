#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   unsigned char p=0, p2=0, p3=0;

   /* print stuff out */
   printf("Res_1: %i\n", p);
   printf("Res_1: %i\n", p<<1);
   printf("Res_1: %i\n", p<<2);
   p2 <<= 1;
   p2 <<= 1;
   printf("Res_1: %i\n", p2);
   printf("Res_1: %i\n", p2);
   p3 |= 0x01;
   printf("Res_1: %i\n", p3);
   p3 |= 0x04;
   printf("Res_1: %i\n", p3);
   p3 |= 0x04;
   printf("Res_1: %i\n", p3);

   return 0;
}
