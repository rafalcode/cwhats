/* here I leanrn how the abs() is only for integeters and fabs() is probably what you're looking for
and that's to be found in the math. library */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[])
{
   double a=.05333;
   double b=-.707;
   double c=.0;
   /* print stuff out */
   printf("Res_1: %6.6f abs %6.6f\n", a, fabs(a));
   printf("Res_2: %a abs %a\n", b, fabs(b));
   printf("Res_3: %a abs %a\n", c, fabs(c));
   // of course abs is for integers, fabs is for floats ad doubles!
   // // .. and it's int he math.h library!!

   return 0;
}
