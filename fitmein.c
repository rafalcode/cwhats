/* go around an array:
 * self avoiding, of course,. too trivial otherwise
 * in this way you are able to compare each element of 
 * an array with all the other elements.
 * in circular fashion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define W 640
#define H 480

void usage(char *name)
{
    printf("Usage for program %s\n", name);
    printf("3 arguments required: 1) quantity 2) wsz 3) hsz\n"); 
}

int main(int argc, char *argv[])
{
    if(argc!=3) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    unsigned N=atoi(argv[1]);
    unsigned w=atoi(argv[2]);
    unsigned h=atoi(argv[3]);

    float wxt, hxt, rat;
    float over;
    for(i=1;i<N;++i) {
        if((W-i*w) <0)
        rat=(float)(i*w-W)/i;
        wxt=(unsigned
        if(W-wxt
        over=(float)(W

    }





    return 0;
}
