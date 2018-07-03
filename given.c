/* give out file names base don input */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *na(char *fname)
{
    char *tc=strrchr(fname, '.');
    char *retc=calloc(3+strlen(fname), sizeof(char));
    sprintf(retc, "%.*s_2%s", (int)(tc-fname), fname, tc);
    return retc;

}

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

   char *nn=na(argv[1]);
   printf("New name is %s\n", nn); 
    free(nn);

   return 0;
}
