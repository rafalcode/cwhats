#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// printing out  1, 2 or 4 bytevlues in small endian format

#define BC  2 // bit containers

void usage(char *name)
{
    printf("Usage for program %s\n", name);
    printf("1 arguments required: 1) the dec value to be converted to hex.\n");
}

int main(int argc, char *argv[])
{
    if(argc!=2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
   int x= atoi(argv[1]);

   printf("Hex: %x\n", x);

   return 0;
}
