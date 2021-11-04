/* insertion sort ref bentley
 *
 * Describing it in english ain't that easy but here goes
 *
 * we compare the first two elemtns and swap them if second is smaller than first
 * we then move to third el and compare i t with all previous elements and 
 * only swap it with one of them if it is bigger than it for the first time
 * and also stopping when comparison with first element is reached */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void simis(int *a, int asz) // Bentley's original three liner
{
    int i, j, tmp;
    for (i = 1; i < asz; i++)
        for (j = i; ((j > 0) && (a[j-1]) > a[j]); j--) {
            tmp=a[j-1]; a[j-1]= a[j];a[j]=tmp;
        }
}

void optis(int *a, int asz) // a slight optimisation .. which is quite obvious, optimises the swap.
{
    int i, j, tmp;
    for (i = 1; i < asz; i++) {
        tmp = a[i];
        for (j = i; ((j > 0) && (a[j-1]) > tmp); j--)
            a[j] = a[j-1];
        a[j] = tmp;
    }
}

int main(int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int i, n=atoi(argv[1]);
    int *arr=malloc(n*sizeof(int));
    for(i=0;i<n;++i)
        arr[i]=(int)(100*(float)rand()/RAND_MAX);
    printf("Random integer array of size %i assigned\n", n); 
    for(i=0;i<n;++i)
        printf("%i ", arr[i]); 
    printf("\n"); 

    // simis(arr, n);
    optis(arr, n);

    for(i=0;i<n;++i)
        printf("%i ", arr[i]); 
    printf("\n"); 
    free(arr);

    return 0;
}
