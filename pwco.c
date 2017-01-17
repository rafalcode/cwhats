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
    for(i=0;i<nr;++i) {
        mj=nc-i;
        for(j=0;j<mj;++j) {
            pwa[mi+j]=na[i+j+1];
            printf("%d/%d ", mi+j, i+j+1);
        }
        printf("\n"); 
        mi+=n-i-1; //multiplier for i
    }

    mi=0;
    char *spapad="    ";
    for(i=0;i<nr;++i) {
        mj=nc-i;
        printf("%d) ", i); 
        for(k=0;k<i;++k) 
            printf("%s", spapad); 
        for(j=0;j<mj;++j) {
            printf("%03d ", pwa[mi+j]);
        }
        mi+=n-i-1; //multiplier for i
        printf("\n"); 
    }

    /* try printing out a full table */
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
    free(na);
    free(pwa);
    return 0;
}
