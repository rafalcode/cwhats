#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define nv 16

int main(int argc, char *argv[])
{
	int i;
	float *xa=malloc((1+nv)*sizeof(float));
	float *sx=malloc((1+nv)*sizeof(float));
	float *cx=malloc((1+nv)*sizeof(float));

	for(i=0;i<=nv;++i) 
		xa[i]=i*2*M_PI/nv;

	for(i=0;i<=nv;++i) 
		sx[i]=sin(xa[i]);
	for(i=0;i<=nv;++i) 
		cx[i]=cos(xa[i]);

	for(i=0;i<nv;++i) 
		printf("%2.4f/%2.4f/%2.4f ", xa[i], sx[i], cx[i]);

	printf("\n"); 
	free(xa);
	free(sx);
	free(cx);
	return 0;
}
