/* go around an array:
 * self avoiding, of course,. too trivial otherwise
 * in this way you are able to compare each element of 
 * an array with all the other elements.
 * in circular fashion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n 4

int main(int argc, char *argv[])
{
    int i, j;
    char a[n];
    for(i=0;i<n;++i) 
        a[i]=i+65;

    for(i=0;i<n;++i) {
        printf("%d) ", i);
        for(j=(i+1)%n;j!=i;j=j+1-(j+1)*((j+1)/n))
            printf("%d ", j);
        printf("\n");
    }

    /* and now .. to finish off, the array itself */
    printf("We have the following array: "); 
    for(i=0;i<n;++i) 
        printf("%c ", a[i]);
    printf("\n"); 

    for(i=0;i<n;++i) {
        printf("Compare %c with: ", a[i]);
        for(j=(i+1)%n;j!=i;j=j+1-(j+1)*((j+1)/n))
            printf("%c ", a[j]);
        printf("\n");
    }

    return 0;
}
