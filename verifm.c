/* I got 2x4=7 yby loose use of the preprocessor (i.e. no parentheses)
 * what#s happening is that the +1 has fairly low precedence allowing
 * and the preprocessor is what it is, a text replacer! */
#include <cairo/cairo.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define HBARNUMS 3
#define VBARNUMS 3
#define NXPTS0 VBARNUMS+1
#define NXPTS (VBARNUMS+1)
#define NYPTS (HBARNUMS+1)

int main (int argc, char *argv[])
{
    int j;

    printf("%i,%i\n", NXPTS, NYPTS); 
    for(j=1; j<NYPTS;++j) { // first col.
        printf("%ix%i=%i ", j, NXPTS0, j*NXPTS0); 
        printf("%ix%i=%i ", j, NXPTS, j*NXPTS); 
        printf("\n"); 
    }
    printf("\n"); 
    return 0;
}
