#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
   double a=.05333;
   double b=-.707;
   /* print stuff out */
   printf("Res_1: %6.6f abs %6.6f\n", b, abs(b));
   printf("Res_2: %a abs %a\n", b, abs(b));
   // of course abs is for integers, fabs is for floats ad doubles!
   // // .. and it's int he math.h library!!

   return 0;
}
