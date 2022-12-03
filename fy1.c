/* I leave this here really just for the record
 * it's a bloomn filter type of way of obtaining random
 * permutations.
 *
 * However, for random permutations you really need the Fisher Yeates algorithm
 * which I call fy0.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int n=atoi(argv[1]);
    if(n>26) {
        printf("Sorry this version only allows a mamimum\n"); 
    int *arr=malloc(n*sizeof(int));
    char alph="a
    int i, j, tmp, r;
    for(i=0;i<n;++i)
        arr[i]=i;

    for(i=n-1;i>=0;--i) {
        r=rand()%(i+1);
        tmp=arr[r];
        arr[r] = arr[i];
        arr[i]=tmp;
    }
    for(i=0;i<n;++i)
        printf("%i ", arr[i]);
    printf("\n"); 
    free(arr);
   return 0;
}
