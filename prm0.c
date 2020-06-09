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

#define llu long unsigned

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int n=atoi(argv[1]);
    size_t lszt=sizeof(llu);
    printf("bytes in type = %zu\n", lszt); 
    printf("bytes in size_t = %zu\n", sizeof(size_t));
    int biit = 8*lszt; // bits in type
    
    int nszt=1+n/biit;
    llu hldr=calloc(nszt, lszt);
    int i, j;

    for(i=0;i<n;++i) 
    int sztr=n%biit;

   return 0;
}
