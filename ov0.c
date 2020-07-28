#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=1) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

   // int a= 0xFFFFFFFF;
   int a= 0x7FFFFFFF;

   /* print stuff out */
   printf("Res_1: %i\n", a);
   printf("Res_1: %i\n", a+1);

   int b=0x8;
   printf("Res_1: %i\n", b);
   printf("Res_1: %i\n", b+1);

   return 0;
}
