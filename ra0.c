/* just messing with random() and endianness */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <math.h>

#define SETSEED 0 // note 300th element on arr2 is actually 1.000 in this run!
#define NRA 8 // number of random numbers required.

int main(int argc, char *argv[])
{
    struct timeval tnow;
    unsigned tseed;
    int i;
    
    gettimeofday(&tnow, NULL);
    /*  use the five last digits of the current microsecond reading to generate a seed */
    // tseed=(unsigned int)((tnow.tv_usec/100000.0 - tnow.tv_usec/100000)*RAND_MAX);
    tseed = SETSEED;
    
    printf("ts=%7.5f\n", (tnow.tv_usec/100000.0 - tnow.tv_usec/100000));
    printf("RAND_MAX (should be max of an int): %u\n", RAND_MAX); 
    int r2=1+RAND_MAX/2; // negatives will have one extra possibility
    printf("1+RMAX/2: %i\n", r2); 
    
    srand(tseed);
    printf("time-seed came out as: %u\n", tseed); 

    int *iarr=malloc(NRA*sizeof(int));
    float *farr=malloc(NRA*sizeof(float));

    for(i=0;i<NRA;++i) {
        iarr[i]=rand()-r2;
        printf("%i ", iarr[i]); 
    }
    putchar('\n');
    printf("as hex:\n"); 
    for(i=0;i<NRA;++i) {
        printf("%x ", iarr[i]); 
    }
    putchar('\n');
    for(i=0;i<NRA;++i) {
        farr[i] = (float)iarr[i]/r2;
        printf("%4.4f ", farr[i]); 
    }
    putchar('\n');
    
    unsigned short *sarr=malloc(2*NRA*sizeof(unsigned short));
    unsigned short *sarr2=malloc(2*NRA*sizeof(unsigned short));
    int *iarr2=malloc(NRA*sizeof(int));
    printf("Shorts rendered as hex:\n"); 
    for(i=0;i<NRA;++i) {
        sarr[2*i] = (iarr[i]>>16)&0x0000FFFF;
        sarr[2*i+1] = iarr[i]&0x0000FFFF;
        printf("%4.4x %4.4x ", sarr[2*i], sarr[2*i+1]);
    }
    putchar('\n');
    printf("Integerised version of the shorts:\n");
    for(i=0;i<NRA;++i) {
        // printf("%i %i ", (int)sarr[2*i], (int)sarr[2*i+1]); 
        printf("%hi %hi ", sarr[2*i], sarr[2*i+1]); 
    }
    putchar('\n');
    printf("Let's add the shorts, see what happens, lesson learnt, cast unsigned to sign shorts first, then integerise:\n");
    for(i=0;i<NRA;++i) {
        printf("Add %i and %i: ", (short)sarr[2*i], (short)sarr[2*i+1]);
        iarr2[i] = (short)sarr[2*i]+(short)sarr[2*i+1];
        printf("%i\n", iarr2[i]);
    }
    printf("\n"); 
    printf("Those additions in hex:\n"); 
    for(i=0;i<NRA;++i)
        printf("%4x ", iarr2[i]);
    printf("\n");
    printf("Let's change endianness to small (HSB comes after LSBs)\n"); 
    for(i=0;i<NRA;++i) {
        sarr2[2*i] = (iarr[i]>>24)&0x000000FF;
        sarr2[2*i] |= (iarr[i]>>8)&0x0000FF00;
        sarr2[2*i+1] = (iarr[i]>>8)&0x000000FF;
        sarr2[2*i+1] |= (iarr[i]<<8)&0x0000FF00;
        printf("%x %x ", sarr2[2*i], sarr2[2*i+1]); 
    }
    printf("\n");
    printf("Numberize the changed endianness for interest:\n"); 
    for(i=0;i<NRA;++i)
        printf("%i %i ", (int)sarr2[2*i], (int)sarr2[2*i+1]);
    putchar('\n');



    printf("Final exercises with shorts:\n"); 

    short s1=0x7FFF;
    short s2=0x0002;
    short s3=0xFFFE;
    printf("%x, %x, %x\n", s1, s1+s2, s3); 
    printf("%hi, %hi, %hi\n", s1, s1+s2, s3); 


    free(sarr2);
    free(sarr);
    free(iarr2);
    free(iarr);
    free(farr);
    return 0;
}
