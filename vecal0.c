#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FQUAN 16

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=1) {
		printf("Error. no args\n");
		exit(EXIT_FAILURE);
	}

    int i;
   float down=445.675-303.209;
   float sy[FQUAN] = {596, 576, 562, 542, 522, 483, 463, 449, 429, 409, 395, 356, 342, 303, 283, 263};
   printf("New python array:\n[");

   float sy2[16]={0};
   for(i=0;i<FQUAN;++i)
       sy2[i]=sy[i]-down;

   float i12=sy2[12];
   sy2[11]=sy2[12]+17;

   for(i=0;i<FQUAN;++i)
       printf((i!=FQUAN-1)? "%4.4f,":"%4.4f]\n", sy2[i]);

   return 0;
}
