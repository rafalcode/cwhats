/* make a pairwise comparison table .. list out a table
 * where the index of the row represents the first of the pair, and each member of the row represents
 * the indices of the original sequence that they are compared with */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!=2) {
        printf("Error. Pls supply argument (integer).\n");
        exit(EXIT_FAILURE);
    }

    int i, j, mi, mj, k;
    int n=atoi(argv[1]);

    int *na=calloc(n, sizeof(int));
    for(i=0;i<n;++i) 
        na[i]=i;

    int npwc=n*(n-1)/2; // wll known, from the maths.
    int *pwa=calloc(npwc, sizeof(int));
    int nr=n-1; // numbner of rows oour pairwise comp table will have
    int nc=n-1;
    printf("Total PWCT size: %i / Num rows: %i / Num cols: %d\n", npwc, nr, nc);
    mi=0;
	printf("Straight:\n"); 
    k=0;
    for(i=0;i<nr;++i) {
        k++;
        mj=nc-i; // gradually decreasing extent of the column run
        for(j=0;j<mj;++j) {
            pwa[mi+j]=na[i+j+1];
            printf("%d/%d/%d ", i+k+mi+j, mi+j, i+j+1);
        }
        printf("\n"); 
        mi+=n-i-1; // cumulative start position for the column run.
    }

    /*render a normal matrix */
    printf("render a normal matrix:\n");
    int *m=calloc(n*n,sizeof(int));
    k=0; // free-floating
    for(i=n-nr;i<n;++i) {
        mj=n-i+1; // gradually decreasing extent of the column run
        for(j=n-nc;j<mj;++j) {
            m[mi+j-1]=na[i+j-1];
        }
        mi+=n-i-1; // cumulative start position for the column run.
    }
    printf("Matrix rendition:\n"); 
    for(i=0;i<n;++i) {
        for(j=0;j<n;++j)
            printf("%d ", m[n*i+j]);
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
    free(m);
    return 0;
}
