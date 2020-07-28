#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply 1 argument: name of xlsx file.\n");
		exit(EXIT_FAILURE);
	}

   char *tmp=NULL;
   tmp=strchr(argv[1], '.');
   char *sysCall=calloc(256,sizeof(char));

   if(strcmp(tmp+1, "xlsx")) {
		printf("Error. Input file must have .xlsx extension.\n");
		exit(EXIT_FAILURE);
   }
   char *csvnam=calloc(strlen(argv[1]),sizeof(char));
   sprintf(csvnam, "%.*s.csv", (int)(tmp-argv[1]), argv[1]);
   // sprintf(sysCall, "ssconvert -S -T Gnumeric_stf:stf_csv %s %s.csicakir.xlsx kir.csv", argv[1], ;

   /* print stuff out */
   printf("Res_1: %s\n", csvnam);
   free(csvnam);
   free(sysCall);

   return 0;
}
