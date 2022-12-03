/* Fisher Yates and making it look like
 * which I call fy0.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASZ 27 // could get away with 26, but not bothering.

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=4) {
		printf("Error. Three args: 1) Size of source array (alphabet will be used: max=26) 2) integer (var q), the size of subset, 3) integer, (var p) number of permutations required.\n");
		exit(EXIT_FAILURE);
	}
    int i, j, k, tmp, r, n, q, p, r0, r2;
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
    int *arr2=malloc(p*q*sizeof(int));

    // fy0.c dealt with the straight indices, in reality we will work with  particular array
    char alph[ASZ]="abcdefghijklmnopqrstuvwxyz"; // need 27 for this.

    printf("%i words of %i characters, from a pool comprised of the first %i alphabet characters (first row without replace, second row with replace):\n", p, q, n); 

    k=0;
    for(j=0;j<p;++j) {

        // the core of Fisher Yeates: this is for "without replacement"
        for(i=n-1;i>=0;--i) {
            r=rand(); // we're going to use this call for both with-replace and without
            // printf("r=%i\n", r); 
            // Fisher Yates
            r0=r%(i+1);
            tmp=arr[r0];
            arr[r0] = arr[i];
            arr[i]=tmp;
            //with replace:
            if(i<q) {
                r2=r%n;
                arr2[k*q+i]=arr[r2];
            }
        }
        // May be we want "with replacement" like R's sample() function.
        // In one sense this is easier, but in another it isn't
        // we can't use the inline method, because it would disturb the randomality.
        // for(i=0;i<q;++i) {
        //     r=rand()%n;
        //     arr2[k*q+i]=arr[r];
        // }
        k++;

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

    // now print the with replacement in their own rows.
    for(j=0;j<p;++j) {
        for(i=0;i<q;++i)
            putchar(alph[arr2[j*q+i]]);
        putchar((j==(p-1))?'\n':' '); 
    }

    free(arr);
    free(arr2);
    return 0;
}
