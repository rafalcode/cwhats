// sscanf'ing strings ... not easy.
// sscanf is good with %d, but %s is very greedy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

   char *outn=calloc(64, sizeof(char));
   sscanf(outn, "
   free(outn);

   return 0;
}
