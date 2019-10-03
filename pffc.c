/* print me a freeform string:
   Elementary exercise that I don't appear to be abel to get right */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls supply argument (name of file).\n");
        exit(EXIT_FAILURE);
    }
    char *tc=argv[1];

    while(*tc)
        putchar(*tc++);
    putchar('\n');

    return 0;
}
