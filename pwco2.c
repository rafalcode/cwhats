/* make a pairwise comparison table (PWCT) .. list out a table
 * where the index of the row represents the first of the pair, and each member of the row represents
 * the indices of the original sequence that they are compared with */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define OFFSET 1

typedef unsigned char boole;
typedef struct
{
	float x,y;
} cartpos;  /* a cartesian position, to lend reality. */

typedef struct
{
    int i,j;
    float d;
} ptdst; // point distances.

int main(int argc, char *argv[])
{
    if(argc!=2) {
        printf("Error. Pls supply argument (integer).\n");
        exit(EXIT_FAILURE);
    }

    int i, j, mi, mj;
    int n=atoi(argv[1]);

    /* OK, here we have our collection of elements that we wish to pair up in all possible combos */
    cartpos *na=calloc(n, sizeof(cartpos));
	printf("We printout the points, these are random points inside a unit square\n"); 
    for(i=0;i<n;++i) {
        na[i].x=(float)rand()/RAND_MAX;
        na[i].y=(float)rand()/RAND_MAX;
		printf("Pt.%i=(%2.4f,%2.4f) ", i+1, na[i].x, na[i].y);
	}
	printf("\n");

    int npwc=n*(n-1)/2; // well known, from the maths.

    /* We're going to create a holder for the 1to1 relationships.*/
    float *pwa=calloc(npwc, sizeof(float));
    ptdst *pwa=malloc(npwc*sizeof(ptdst));
    int nr=n-1; // number of rows our pairwise comp table will have
    int nc=n-1;
    printf("Total PWCT size: %i / Num rows: %i / Num cols: %d\n", npwc, nr, nc);

    printf("PWA a pairwise op array of size %d. Holds results of all pairwise ops like so:\n", npwc); 
    mi=0;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        for(j=0;j<mj;++j) {
            pwa[mi+j].d=sqrt(pow((na[i].x-na[i+j+1].x), 2)+pow((na[i].y-na[i+j+1].y), 2));
            pwa[mi+j].x = i;
            pwa[mi+j].y = i+j+1;
            printf("p%d/%d.vs.%d=%2.4f ", mi+j, i, i+j+1, pwa[mi+j].d);
        }
        printf("\n"); 
        mi+=n-i-1; // cumulative start position for the column run.
    }

    printf("Pretty print of pwa:\n"); 
    j=0;
    mi=0;
    int k, kk;
    printf("FROM:/TO: "); 
    for(i=1;i<n;++i)
        printf("p_%d    ", i); 
    printf("\n");
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        printf("p_%d:    ", i);
        for(k=0;k<i;++k) 
            for(kk=0;kk<7;++kk) 
                putchar(' '); // filler
        for(j=0;j<mj;++j) {
            printf("%2.4f ", pwa[mi+j]);
        }
        printf("\n"); 
        mi+=n-i-1; // cumulative start position for the column run.
    }

    /* now render a square matrix out of the pwa: nope just uses the members matrix. */
    mi=0;
    float *ma=calloc(n*n,sizeof(float));
    int m;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        m=(nr+1)*i;
        for(j=0;j<mj;++j) {
            printf("%i:%i ", m+i+j+1, i+j+1);
            // ma[m+i+j+1]=na[i+j+1]; // if direct from na
            ma[m+i+j+1]=pwa[mi+j];
        }
        printf("\n");
        mi+=n-i-1; // cumulative start position for the column run.
    }
    printf("\n");

    free(na);
    free(pwa);
    free(ma);
    return 0;
}
