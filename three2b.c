#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/* this program was made to investiaget how one might downsample 32 bits to 16
 * and I wondering it's as easy as just downshifting the samples.
 * ANd it appears to be true. Increidbly enough. */

#define NUMS 12
#define BITS 3
#define BITS2 2
#define P ((1<<BITS)-1) // max val with bits available.
#define P2 ((1<<BITS2)-1) // max val with bits available.

int main(void)
{
    setlocale(LC_NUMERIC, "");

    printf("%x \n", (1<<4)-1);
    int i;
    int *NA=malloc(NUMS*sizeof(int));
    int *NA2=malloc(NUMS*sizeof(int));
    float *FA=malloc(NUMS*sizeof(float));
    for(i=0;i<NUMS;++i) {
        NA[i]=rand();
        NA[i] &= P;
        FA[i]= (float)NA[i]/(float)P;
        // get 1.0000 0.6667 0.3333 1.0000 0.3333 1.0000 0.6667 0.0000 0.3333 0.3333 0.6667 1.0000
        FA[i] *= 2.0;
        FA[i] -= 1.0;
        /* because we seek signed integers, and it is imperative to have max and minimums, and of course we have binary
         * we get into trouble with no value for 0.0. The most htat can be hoped is that the two values on either side of zero
         * are as close as possible to it, and this can only be done by having more bits. */
    }
        
    for(i=0;i<NUMS;++i) 
        //printf("%'li ", NA[i]);
        printf("%04x ", NA[i]);
    printf("\n"); 
    for(i=0;i<NUMS;++i) 
        printf("%6.4f ", FA[i]);
    printf("\n"); 
    for(i=0;i<NUMS;++i) {
        NA2[i] = NA[i]>>(BITS-BITS2);
        FA[i]= (float)NA2[i]/(float)P2;
        FA[i] *= 2.0;
        FA[i] -= 1.0;
    }
    for(i=0;i<NUMS;++i) 
        printf("%04x ", NA2[i]);
    printf("\n"); 
    for(i=0;i<NUMS;++i) 
        printf("%6.4f ", FA[i]);
    printf("\n"); 


    free(NA2);
    free(NA);
    free(FA);
    return 0;
}
