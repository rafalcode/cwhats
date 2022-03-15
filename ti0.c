#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    struct timeval tnow;
    gettimeofday(&tnow, NULL);
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

   /* declarations */
   FILE 
   char
   int
   float
   double

   /* print stuff out */
   printf("Res_1: %s\n", "somedata");

   return 0;
}
