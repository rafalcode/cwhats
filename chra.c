// the range of a char, and when turns neg
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define n 8

struct r
{
    int i;
    struct r *r;
};
typedef struct r r_t;

int main(int argc, char *argv[])
{
    // check when char turns neg.
   char a0=0x80, a1=0x81, a2=0xFF;
   printf("%x %x %x\n", a0, a1, a2); 
   printf("%i %i %i\n", a0, a1, a2); 

   int i, j;
   char *b=malloc(2*n*sizeof(char));
   for(i=0;i<n;++i) {
       b[2*i]=65+2*i;
       b[2*i+1]=65+2*i+1;
   }

   int i0[n]={0};
   for(i=0;i<n;++i) {
       // here we isolate last bit to identify evens and unevens, shift left 1 (which is same as *2)
       // and substrat 1, so that out 0's become -1's and 1's stay as 1's.
       // howevert this starts with -1, then +1: we want opposite, so the ! negates
       // and sequence then starts with +1.
       i0[i]=((!(i&0x01))<<1)-1;
   }

   int k=0;
   for(i=0;i<n;++i) {
       // k will go from 0 to 1 and stop at 2
       // then from 1 to 0 and stop at -1
       while((k!=2) & (k!=-2)) {
           printf("%i:%i:%c ", k, 2*i+k, b[2*i+k]); 
           k+=i0[i];
       }
       k-=i0[i];
   }
   printf("\n"); 

   /* ring idea
   r_t *rr=malloc(sizeof(r_t));
   rr[0].i=0;
   rr[1].i=1;
   rr[0].r=rr+1;
   rr[1].r=rr+0;

   for(i=0;i<n;++i) 
       printf("%i ", rr[i&0x01]); 
       not working out so well
       */
   // chatgpt soln shows I ned to tap into XOR
   int i2;
   for(i=0;i<n*4;++i) {
       i2=i ^ ((i >> 1) & 0x1); 
       printf("%i ", i2); 
   }
   printf("\n"); 



   return 0;
}
