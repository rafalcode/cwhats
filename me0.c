#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prtv(int *v, int vsz)
{
    int i;
    printf("New ord:\n"); 
    for(i=0;i<vsz;++i) 
        printf("%i ", v[i]);
    printf("\n"); 
}

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=1) {
		printf("Error. Pls supply argument (name of file).\n");
		exit(EXIT_FAILURE);
	}

    int i,j;
    int v[8] = {3, 32, 42, 69, 20, 25, 63, 86};
    i=0;
    j=4;
    while(i<4) { 
        while(j<8) {
            while(v[i]>v[j])
                j++
            {
                tmp=v[j]; v[j]=v[i], v[i]=tmp; //swap!
            } else {
                i++;
            }
            prtv(v, 8);
        }
    }

    return 0;
}
