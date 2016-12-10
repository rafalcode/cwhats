#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
/* this program was made to investiaget how one might downsample 32 bits to 16
 * and I wondering it's as easy as just downshifting the samples.
 * And if so, what about little endianism?
 * Might C take care of this? */

/* later note: you shouldn't use higher level containers such as int. You should work as close to raw as possible, and that's unsigned char. */

#define SD 10
#define NUMS 20
#define BITS 4
#define BITS2 3
#define P ((1L<<BITS)-1) // max val with bits available.
#define P2 ((1L<<BITS2)-1) // max val with bits available.

int main(void)
{
    setlocale(LC_NUMERIC, "");
    srand(SD);
    // printf("%x \n", (1<<4)-1);
    int i;
    int *NA=malloc(NUMS*sizeof(int));
    int *NA2=malloc(NUMS*sizeof(int));
    float *FA=malloc(NUMS*sizeof(float));
    for(i=0;i<NUMS;++i) {
        NA[i]=rand(); // only gives [0,+]
        // NA[i] &= P;
        NA[i] &= (0xff<<24); // masks the MSB of the generated rand
        NA[i] >>= 24; // sends MSB down to LSB
        NA[i] &= P;
        NA[i] -= 1L<<(BITS-1); // allow negatives to reflect signed
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
        printf("%i ", NA[i]);
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
        printf("%i ", NA2[i]);
    printf("\n"); 
    for(i=0;i<NUMS;++i) 
        printf("%6.4f ", FA[i]);
    printf("\n"); 


    free(NA2);
    free(NA);
    free(FA);
    return 0;
}
