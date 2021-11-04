#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define LIM 10000000

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int n=atoi(argv[1]);

   int i, sq;
   unsigned char mkr=0;

   for(i=0;i<LIM;++i) {
       sq = pow(i, 2);
       if(n>sq)
           continue;
       else if(n<sq) {
           mkr=1;
           break; // overshot
       } else
          break; 
   } 
   if(mkr==1)
       printf("Not square\n"); 
   else
       printf("Yes square\n"); 

   return 0;
}
