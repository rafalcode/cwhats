#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// printing out  1, 2 or 4 bytevlues in small endian format

#define BC  2 // bit containers

void usage(char *name)
{
    printf("Usage for program %s\n", name);
    printf("1 argument required: 1) the float value (prob 0-1) to be converted to -10log10(val).\n");
}

int main(int argc, char *argv[])
{
    if(argc!=2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
   float x= atof(argv[1]);
   float val=-10*log10(x);

   printf("minlog10: %4.6f\n", val);

   return 0;
}
