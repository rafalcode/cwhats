/* approximations to pi and what they might tell you about differences and accuracies 
 * taken from
 * https://en.wikipedia.org/wiki/Approximations_of_%CF%80
 *  you cannot depend
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

#define M_PI 3.14159265358979323846

int main(int argc, char *argv[])
{
   int i;
   // (famous) approximations to pi
   double f2[]= {22./7, 223./71, 339./108, 256./81, 25./8, 3.14, 3.1416, 3.141589625, 0x1.921fp+1}; // that last one is my own
   int asz = sizeof(f2)/sizeof(double);

   printf("True pi= %4.2f %4.4f %4.12f\n%4.36f, %a\n", M_PI, M_PI, M_PI, M_PI, M_PI); 
   printf("\n"); 
   for(i=0;i<asz;++i) 
       printf("%4.6f - %a\n", f2[i], f2[i]); 
   printf("\n"); 

   return 0;
}
