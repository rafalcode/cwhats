/* 2 for loops in one?
 * We're used to the single index forloop, but actually
 * it can cope with more. Let's have a look ... */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i, j;
    for(i=0,j=0;((i<4)&(j<4));++i,j+=2) 
        printf("%d ", 2*i+j);
    printf("\n"); 
    return 0;
}
