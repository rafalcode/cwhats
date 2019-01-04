/* scanning floats from a string using sscanf:
 * when scanning from files, the file pointer moves automatically
 * along hte file: not so with strings. Here is a way of reading bytes consumed */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *p="  3.49 4.1111 \n\n       3.3333    9.919199";
    float f[4];
    int i, fcou /* captured-floats-so-far count*/, bcou /*equiv of floats, but in bytes */;
    int totfcou = 0 /* total float count */, totbcou = 0;

    while ( ( fcou = sscanf(p + totbcou, "%f%n", f + totfcou, &bcou )) > 0 ) {
        /* what's what:
         * p+totbcou is fairly clear, totbcou is the offset by which we move along the string
         * f+totfcou is similar, but it's the destination of the float,
         * i.e. the array position it should be dropped into.
         */
        totbcou += bcou;
        totfcou += fcou;
    }

    for(i=0;i<4;++i) 
        printf("%f\n", f[i]); 

    return 0;
}
