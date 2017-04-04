/* Can we deal with an array of unknown size?
 * I suppose we shouldn't have to. All aray size must be know in advance, sure.
 * But can we?  I suppose it would need a marker or sentinel */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

	int i;
	// a[4]={3,5,1,3};
	int *a=malloc(4*sizeof(int));
	for(i=0;i<4;++i) 
		printf("%p ", a+i);
	printf("\n"); 
	(a+i)=NULL;
	printf("%p ", a+i);
	printf("\n"); 
	free(a);

   return 0;
}
