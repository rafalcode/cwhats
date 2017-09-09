#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 11

int main(int argc, char *argv[])
{
	int i, j;
	int midp=n/2;
	if(midp%2==1)
		midp++;
	int *ia=malloc(n*sizeof(int)); // index array, as in array of indices
	j=0;
	for(i=0;i<midp;i++) {
		ia[j]=i;
		j+=2;
	}
	j=1;
	for(i=n-1;i>=midp;i--) {
		ia[j]=i;
		j+=2;
	}

	printf("This is a series of od different ways to travel along a linera array\n"); 
	printf("First off: bounce from one end to the other until reaching the middle.\n"); 
	for(i=0;i<n;++i) 
		printf("%i ", ia[i]); 
	printf("\n"); 

	free(ia);
	return 0;
}
