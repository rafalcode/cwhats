#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OFFSET 1

void mirf(int *m, int n) // forward slash notation: mirror upper right triangular onto low left triangular.
{
    int i, j, piv;
    for(i=0;i<n;++i)  // reset diagonal to zero first : creates a forward slash
        m[n*i+i]=0;

    for(i=1;i<n;++i) {
        piv=OFFSET+i;
        for(j=0;j<piv-1;++j)
            m[n*i+j]=m[n*j+i];
    }
    return;
}

void mirr(int *m, int n) // reverse slash notation: mirror upper left triangular onto low right triangular.
{
    int i, j, piv;
    for(i=0;i<n;++i)  // reset diagonal to zero this is the backward slash diagonal
        m[n*i+n-1-i]=0;

    for(i=1;i<n;++i) {
        piv=n-1-i;
        for(j=piv; j<n;++j)
            // m[n*i+j]=m[n*(n-1-j)+n-1-i];
            m[n*(n-1-j)+n-1-i] = m[n*i+j];
    }
    return;
}

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls supply argument (name of file).\n");
        exit(EXIT_FAILURE);
    }
    int i, j, n =atoi(argv[1]);
    int *m=calloc(n*n, sizeof(int));
    for(i=0;i<n;++i) 
        for(j=0;j<n;++j) 
            m[n*i+j]=n*i+j+1;

    for(i=0;i<n;++i) {
        for(j=0;j<n;++j) 
            printf("%02d ", m[n*i+j]);
        printf("\n"); 
    }
    printf("\n"); 
    /* print stuff out */
    mirr(m, n);

    for(i=0;i<n;++i) {
        for(j=0;j<n;++j) 
            printf("%02d ", m[n*i+j]);
        printf("\n"); 
    }
    free(m);
    return 0;
}
