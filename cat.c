#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   char *f="123.465456";
   char *f1="123.465456000";
   char *f2="123.46545600000";
   char *e="000000";
   // printf("%s\n", strcat(f,e)); 
   printf("%4.*f\n", 9, strtod(f, NULL));
   printf("%4.*f\n", 9, strtod(f1, NULL));
   printf("%4.*f\n", 9, strtod(f2, NULL));

   return 0;
}
