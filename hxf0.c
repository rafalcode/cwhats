/* Hex floats!
 *
 * This makes use of the C99 printf token "%a"
 * which shows you the proper representation of a float
 * "without the gunk"
 * it's easy to be too clever by half with it though
 * read https://www.reddit.com/r/cpp/comments/pweba1/hexadecimal_floatingpoint_literals/
 * */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   int i;
   float f1[]= {0.5, 0.25, 0.125, 0.1, 0.3, .00000000001, .005, .00125};
   float hf1[]= {0x2p-1,0x3p-1,0x2p-4,0x3p-4};
    // float f2[]= {1./4, 1./8, 3./8, 1./16, 3./16};
   float f2[]= {1./4, 1./8, 1./16, 1./32, 1./64, 1./128, 1./256};
   int asz = sizeof(f2)/sizeof(float);
   int hasz = sizeof(hf1)/sizeof(float);
   printf("nummembs=%i\n", asz);

   /* print stuff out */
   for(i=0;i<asz;++i) 
       printf("%a(%4.12f)\n", f2[i], f2[i]); 
    // for(i=0;i<hasz;++i) 
    //    printf("%a(%4.12f)\n", hf1[i], hf1[i]); 
    char *fc="0x1.9p-4";
    float ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x1.ap-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x1p-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x7p-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x8p-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x9p-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x9p-8";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0x9p-12";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 
    fc="0xap-4";
    ff=strtod(fc, NULL);
    printf("%s is %4.6f is %a\n", fc, ff, ff); 


    printf("The overall gist to this is that it's best to think in terms of nybbles, as in 4bit sequences\n");
    printf("and the first one represents sixteenths, the second twofivesixth's etc etc. It's probably\n");
    printf("best to calle them "p-4"ths, p-8ths, p-12ths to make it pronounceable at least's probably\n");
   return 0;
}
