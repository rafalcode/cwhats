/* Lesson in passing in a sructure to a function
 * and how to get it to change. I've foten used a dummy variable within
 * the function, but this turns out to be not so clever, as demonstratd here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int tb;
	int nsq;
} smm_t;


void changeit(smm_t *smm)
{
	smm_t smm2=*smm;
	printf(" incoming smm.tb = %i smm.nsq = %i\n",smm->tb, smm->nsq);
	smm2.tb +=8;
	smm2.nsq +=3;
	smm->tb +=2;
	smm->nsq +=1;
	// smm=&smm2;
	return;
}

int main(int argc, char *argv[])
{
	int i;
	smm_t smm={2,1};
	for(i=0;i<4;++i) 
		changeit(&smm);
	printf("%d %d\n", smm.tb, smm.nsq); 

   return 0;
}
