/* more experimentation assigning literals */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   float f[3];

   *f={99,99,99};

   /* print stuff out */
   printf("Res_1: %4.4f\n", f[1]);

   return 0;
}
