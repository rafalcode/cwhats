#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("%s, generates a one line sequence of random numbers, depending on size/length value (argument 1) and max value of random integer (argument 2)\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int i, len=atoi(argv[1]), mxv=1+atoi(argv[2]);

    for(i=0;i<len;++i) 
        printf((i==len-1)?"%i\n":"%i,", (int)(mxv*(float)rand()/RAND_MAX));

    return 0;
}
