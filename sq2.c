/* checking if a certain number is a square without using math library. 
 * Secret is exhaustive forlooping as usual */

#include <stdio.h>
#include <stdlib.h>

#define LIM 0x8FFFFFFF

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int n=atol(argv[1]);
    printf("%zu\n", sizeof(n)); 

   int i;
   long long sq;
   unsigned char mkr=0;

   for(i=0;i<LIM;++i) {
       sq = i*i;
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
