// how to define an array of string literals
// it's no problem! See below!
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   // char *s= "sorry";
   char *s[2]= {"sorry", "nogo"};

   /* print stuff out */

   // printf("%s\n", s);
   printf("%s\n", s[1]);

   return 0;
}
