#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define NUMS 10

// printing witht he thousands separator
int main(void)
{
    setlocale(LC_NUMERIC, "");

    int i, *NA=malloc(NUMS*sizeof(int));
    for(i=0;i<NUMS;++i) 
        NA[i]=rand();

    print("RAND_MAX is %d\n", RAND_MAX);
    for(i=0;i<NUMS;++i) 
        printf("%'d ", NA[i]);
    printf("\n"); 

    free(NA);
    return 0;
}
