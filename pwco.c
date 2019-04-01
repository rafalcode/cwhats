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

void mirb(float *m, int n, boole cpdown) // forward slash notation: mirror upper right triangular onto low left triangular.
{
    int i, j, piv;
    // for(i=0;i<n;++i)  // reset diagonal to zero first : creates a forward slash
        // m[n*i+i]=0;

    for(i=1;i<n;++i) {
        piv=OFFSET+i;
        for(j=0;j<piv-1;++j)
            if(cpdown ==1) // copy upper entries down onto lower
                m[n*i+j]=m[n*j+i];
            else if(cpdown ==0) // copy lower entries up onto upper
                m[n*j+i]=m[n*j+i];
    }
    return;
}

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
    int nr=n-1; // number of rows our pairwise comp table will have
    int nc=n-1;
    printf("Total PWCT size: %i / Num rows: %i / Num cols: %d\n", npwc, nr, nc);

    printf("PWA a pairwise op array of size %d. Holds results of all pairwise ops like so:\n", npwc); 
    mi=0;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        for(j=0;j<mj;++j) {
            pwa[mi+j]=sqrt(pow((na[i].x-na[i+j+1].x), 2)+pow((na[i].y-na[i+j+1].y), 2));
            printf("p%d/%d.vs.%d=%2.4f ", mi+j, i, i+j+1, pwa[mi+j]);
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
        mi+=n-i-1; // cumulative start position for the column run.
        // mi+=n; // Some sort of alternative
    }
    printf("\n");
    mirb(ma, n, 1); //copy upright to down left

    /* now render a square matrix out of the pwa: nope just uses the members matrix.
    int *ma=calloc(n*n,sizeof(int));
    int m;
    mi=0;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        m=(nr+1)*i;
        for(j=0;j<mj;++j) {
            ma[mi+j]=na[i+j+1];
            printf("%d/%d ", mi+j, i+j+1);
        }
        printf("\n"); 
        mi+=n; // cumulative start position for the column run.
    }
    // */

    printf("Matrix rendition:\n"); 
    for(i=0;i<n;++i) {
        for(j=0;j<n;++j)
            printf("%2.4f ", ma[n*i+j]);
        printf("\n"); 
    }
	

/*
    printf("totherway:\n"); 
    mi=0;
    for(i=0;i<nr;++i) {
        mj=i+1; // gradually decreasing extent of the column run
        for(j=0;j<mj;++j) {
            // pwa[mi+j]=na[i+j+1];
            printf("%d/%d ", mi+j, i+j+1);
        }
        printf("\n"); 
        mi+=i+1; // cumulative start position for the column run.
    }
    mi=0; // cumulative starting indec for each i
    char *spapad="    ";
    for(i=0;i<nr;++i) {
        printf("%03d ", i); 
        for(k=0;k<i;++k) 
            printf("%s", spapad); 
        mj=nc-i; // current extent of the j variable
        for(j=0;j<mj;++j) {
            printf("%03d ", pwa[mi+j]);
        }
        mi+=n-i-1; 
        printf("\n"); 
    }

    mi=0;
    printf("Reverse:\n"); 
    for(i=0;i<nr;++i) {
        printf("%d) ", i); 
        mj=nc-i; // current extent of the j variable
        for(j=0;j<=i;++j) {
            printf("%03d ", pwa[mi+j]);
        }
        mi+=n-i-1; 
        printf("\n"); 
    }

    k=0;
    for(i=0;i<3;++i) {
        for(j=0;j<=i;++j) {
            printf("%d ", k++);
        }
        printf("| ");
    }
    printf("\n"); 

    // try printing out a full table
    mi=0;
    int mir=npwc-1-mi;
    printf("mi=%d/mir=%d\n", mi, mir); 
    for(i=0;i<nr;++i) {
        mj=nc-i;
        printf("%d) ", i); 
        for(k=0;k<i;++k) 
            printf("%03d ", pwa[mir+mj-k-1]);
        for(j=0;j<mj;++j) {
            printf("%03d ", pwa[mi+j]);
        }
        mi+=n-i-1; //multiplier for i
        mir=npwc-mi-1; // reverse mj
        printf("\n"); 
        printf("mi=%d/mir=%d\n", mi, mir); 
    }
*/
    free(na);
    free(pwa);
    free(ma);
    return 0;
}
