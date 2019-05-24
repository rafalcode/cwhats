/* a bit inconclusive */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 100

int main(int argc, char *argv[])
{
    if(argc!=1) {
        printf("No args for now\n"); 
        exit(EXIT_SUCCESS);
    }
	float somef= 3.0;

    double *ma=malloc(N*sizeof(double));
    memset(ma, (int)somef, N*sizeof(double));

	printf("ma[N/10]=%4.6f\n", ma[N/10]);

    free(ma);

	return 0;
}
