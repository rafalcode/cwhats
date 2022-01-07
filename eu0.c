#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=3) {
        printf("Error. Pls supply 2 integer arguments for the euclidean gcd calculation\n");
        exit(EXIT_FAILURE);
    }

    int m=atoi(argv[1]), n=atoi(argv[2]);
    if(m==n) {
        printf("Error. The two integers cannot be the same, fruitless exercise otherwise.\n");
        exit(EXIT_FAILURE);
    }
    /* get varname a to be larger of two, just to help memory */
    int a=m, b=n;
    if(n>m) {
        b=m;
        a=n;
    }

    /* print stuff out */
    printf("smaller from bigger diff is: %i\n", a-b);

    int mb=b; // multiples of b
    while(mb<=a) {
        mb+=b;
    }


    return 0;
}
