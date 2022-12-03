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
#define ASZ 27

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=4) {
		printf("Error. Three args: 1) Size of source array (alphabet will be used: max=26) 2) integer (var q), the size of subset, 3) integer, (var p) number of permutations required.\n");
		exit(EXIT_FAILURE);
	}
    int i, j, tmp, r, n, q, p;
    n=atoi(argv[1]);
    q=atoi(argv[2]);
    p=atoi(argv[3]);
    if(n>(ASZ-1)) {
        printf("Sorry this version only allows a maximum of %i, due size of US alphabet.\n", ASZ-1); 
		exit(EXIT_FAILURE);
    }
    int *arr=malloc(n*sizeof(int));
    for(i=0;i<n;++i)
        arr[i]=i;

    // fy0.c dealt with the straight indices, in reality we will work with  particular array
    char alph[ASZ]="abcdefghijklmnopqrstuvwxyz";

    printf("%i permutations of %i word comprised of the first %i alphabet characters to be generated:\n", p, q, n); 

    for(j=0;j<p;++j) {

        // the core of Fisher Yeates:
        for(i=n-1;i>=0;--i) {
            r=rand()%(i+1);
            tmp=arr[r];
            arr[r] = arr[i];
            arr[i]=tmp;
        }

        /* DEBUG:
        printf("Permutation of indices:\n"); 
        for(i=0;i<q;++i)
            printf("%i ", arr[i]);
        printf("\n"); 

        printf("Corresponding permutation of target array.:\n"); 
        */
        for(i=0;i<q;++i)
            putchar(alph[arr[i]]);
        putchar((j==(p-1))?'\n':' '); 
    }

    free(arr);
    return 0;
}
