/* pfcofs.c: PrintF Chars of String:
 * A substring printer ... but only using one printf statement */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=4) {
		printf("Error. Pls supply argument 1) a string 2) index of start char 3) length of substring.\n");
		exit(EXIT_FAILURE);
	}
   int si=atoi(argv[2]);
   int l=atoi(argv[3]);

   printf("Substring is:\n");
   // printf("%*.*s\n", 10,l, argv[1]+si);
   printf("%.*s\n", l, argv[1]+si);
   printf("And this is the way to print only a certain number of characters from teh start of the string:\n");
   printf("%.*s\n", l, argv[1]);

   return 0;
}
