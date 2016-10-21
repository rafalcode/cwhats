/* mapping numbers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls supply argument (integer).\n");
        exit(EXIT_FAILURE);
    }

    int n=atoi(argv[1]);
    int i, j, jj, k;
    /* try to advance in twos i.e. two operationss per loopi */
    for(i=2;i<n;i+=2) {
        k=i/8;
        j= i+8;
        printf("%d %d %d %d : ", i, j, k, i*k+8); 
        printf("%d %d %d %d\n", i+1, j, k, i*k+9); 
    }

    return 0;
}
