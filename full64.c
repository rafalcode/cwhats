#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   unsigned long a=0UL;

   /* print stuff out */
   printf("a is %lx\n", a-1UL);
   printf("%lx\n", (1UL<<63)-1UL);
   printf("%lx\n", (1UL<<62)-1UL);
   printf("%lx\n", (1UL<<61)-1UL);
   printf("%lx\n", (1UL<<60)-1UL);
   printf("%lx\n", (1UL<<59)-1UL);

   return 0;
}
