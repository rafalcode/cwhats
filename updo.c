/* up down: this turned out ot be too elaborate .. go to updo2 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASZ 20
#define STP 8

int main(int argc, char *argv[])
{

	int i;
	// a[ASZ]={3,5,1,3};
	char *a=malloc(ASZ*sizeof(char));
	for(i=0;i<ASZ;++i) 
        a[i]=(char)(65+(int)(4*((float)random()/RAND_MAX)));
	for(i=0;i<ASZ;++i) 
        printf("%c ", a[i]);
    printf("\n"); 

    int lim=(ASZ-STP>STP)? STP : ASZ - STP;

    int im, side;
    printf("Starting to look at %i|%c\n", STP, a[STP]); 

    // up
    int upu, dou;
    for(i=STP+1;i<ASZ;++i) {
        if(a[i] == 'A') {
            upu=i;
            break;
        }
        upu=ASZ-1;
    }
    for(i=STP-1;i>=0;--i) {
        if(a[i] == 'A') {
            dou=i;
            break;
        }
        dou=0;
    }

    printf("%i|%i\n", upu, dou);

	free(a);

   return 0;
}
