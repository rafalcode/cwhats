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
#include <math.h>

#define FORI(n); \
    for(int i=0; i<(n); ++i) \
        printf("%i ", i); \
    printf("\n");

#define ASSX(x, cs, n); \
    for(int i=0; i<(n); ++i) \
        (x) += ((int)(cs)[i]-48) * pow(10, ((n)-1-(i)));

#define ASSX0(x, cs, n); \
    for(int i=((n)-1); i>=0; --i) \
        (x) += ((int)(cs)[i]-48);

#define ASSX2(x, cs, n); \
    for(int i=((n)-1); i>=0; --i) \
        (x) += ((int)(cs)[i]-48) * (((n)-(i))*10);

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int x=0;
    size_t sz = strlen(argv[1]);
    ASSX(x, argv[1], strlen(argv[1]));
    printf("sz arg = %zu / x is %i\n", sz, x);
   return 0;
}
