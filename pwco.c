/* make a pairwise comparison table .. list out a table
 * where the index of the row represents the first of the pair, and each member of the row represents
 * the indices of the original sequence that they are compared with */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 1

typedef unsigned char boole;

void mirb(int *m, int n, boole cpdown) // forward slash notation: mirror upper right triangular onto low left triangular.
{
    int i, j, piv;
    for(i=0;i<n;++i)  // reset diagonal to zero first : creates a forward slash
        m[n*i+i]=0;

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

    int i, j, mi, mj, k;
    int n=atoi(argv[1]);

    /* OK, here we have our collection of elements that we wish to pair up in all possible combos */
    int *na=calloc(n, sizeof(int));
    for(i=0;i<n;++i) 
        na[i]=i;

    int npwc=n*(n-1)/2; // well known, from the maths.

    /* We're going to create a holder for the 1to1 relationships.*/
    int *pwa=calloc(npwc, sizeof(int));
    int nr=n-1; // number of rows our pairwise comp table will have
    int nc=n-1;
    printf("Total PWCT size: %i / Num rows: %i / Num cols: %d\n", npwc, nr, nc);
    /*
    mi=0;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        for(j=0;j<mj;++j) {
            pwa[mi+j]=na[i+j+1];
            printf("%d/%d ", mi+j, i+j+1);
        }
        printf("\n"); 
        mi+=n-i-1; // cumulative start position for the column run.
    }
    */
    /* now render a square matrix out of the pwa: nope just uses the members matrix. */
    mi=0;
    int *ma=calloc(n*n,sizeof(int));
    int m;
    for(i=0;i<nr;++i) {
        mj=nc-i; // gradually decreasing extent of the column run
        m=(nr+1)*i;
        for(j=0;j<mj;++j)
            ma[m+i+j+1]=na[i+j+1];
        /// mi+=n-i-1; // cumulative start position for the column run.
        mi+=n; // cumulative start position for the column run.
    }

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
    /* only one half is done however */
    // mirb(ma, n, 1); //copy upright to down left
    // */

    printf("Matrix rendition:\n"); 
    for(i=0;i<n;++i) {
        for(j=0;j<n;++j)
            printf("%d ", ma[n*i+j]);
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
