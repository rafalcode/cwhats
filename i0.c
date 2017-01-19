/* the key to reversing indices is N-1-oldidx
 * where N is the size of the array
 * this may seem obvious,bu hwn you haven't been doign it for a while ...
 * you get rusty */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=3) {
        printf("Error. Pls supply NUmber size of array and selected index");
        exit(EXIT_FAILURE);
    }
    int i;
    /* declarations */
    int N=atoi(argv[1]);
    int j=atoi(argv[2]);
    int *arr=malloc(N*sizeof(int));
    for(i=0;i<N;++i) 
        arr[i]=i+1;
    printf("%d\n", arr[j]); 
    int revi=N-j-1;
    printf("%d\n", arr[revi]); 

    free(arr);
    return 0;
}
