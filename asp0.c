// This is about reducing image and yet retaining the aspect ratio of the original image.
// Actually this is a permanet problem as chatgpt remindd me:
// (Note, chatgpt is hard to nail down, to wit:
//
// Apply the Scaling Factor to the Height:
// New Height
// =
// 1100
// ×
// 0.4167
// ≈
// 458.3
//  pixels
// New Height=1100×0.4167≈458.3 pixels
// 
// You can round this to 458 pixels, giving you new dimensions of 800x458 pixels.
// 
// 3. Effect on the Image
// Slightly Taller Image: Since the original height was greater, the new image will be slightly taller compared to the standard 16:9 aspect ratio.
// No Distortion: The image will still maintain the proportionality of its original aspect ratio, so there will be no stretching or squishing, just a different ratio of width to height.
//
// Crikey look at this
//
// "the aspect ratio changes slightly ... maintaining the new aspect ratio .what? You can't maintain something new.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=5) {
		printf("Error. Pls supply 4 args: 1) w of large image 2) h of same 3) w of reduced image 4) h of same\n");
        printf("example: ./asp0 4000 3000 900 600\n"); 
        printf("the first two example: ./asp0 4000 3000 900 600\n"); 
		exit(EXIT_FAILURE);
	}
   
    double wha[2]={atof(argv[1]), atof(argv[2])};
    double aspa, aspb; // this is what has to be observed
    printf("\n"); 
    double whb[2]={atof(argv[3]), atof(argv[4])};
    double howm0;

    aspa=wha[0]/wha[1];
    aspb=whb[0]/whb[1];
    printf("asps: %2.6f %2.6f\n",aspa, aspb); 
    if((aspb>aspa) & (aspa>1)) {
        printf("A landscape image: height of a needs biggest reduction. Width of image a will therefore be some way less than width of image b.\n");
        howm0=wha[1]/whb[1];
    } else if((aspb<aspa) & (aspa>1)) {
        // width of image a needs biggest reduction.
        printf("A landscape image: width of image a needs biggest reduction. Height of image a will therefore be some way less than width of image b.\n");
        howm0=wha[0]/whb[0];
    } else if((aspb<aspa) & (aspa<1)) {
        printf("A portrait image: width of image a needs biggest reduction. Height of image a will therefore be some way less than width of image b.\n");
        howm0=wha[0]/whb[0];
    } else if((aspb>aspa) & (aspa<1)) {
        printf("A portrait image: height of a needs biggest reduction. Width of image a will therefore be some way less than width of image b.\n");
        howm0=wha[1]/whb[1];
    }
    printf("aspa=%2.6f\n", aspa); 
    printf("howm0=%2.6f\n", howm0); 
    printf("Use howm0 to reduce wha[0]=%2.6f\n", wha[0]/howm0); 
    printf("Use howm0 to reduce wha[1]=%2.6f\n", wha[1]/howm0); 
    int whf[2]= { (int)floor(wha[0]/howm0), (int)floor(wha[1]/howm0) };
    printf("whf: %i %i \n",whf[0], whf[1]); 
    printf("new asp=%2.6f\n", (double)whf[0]/whf[1]); 

   return 0;
}
