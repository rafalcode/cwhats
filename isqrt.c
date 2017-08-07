/* the famous inverse square root: 32 bit only */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float InvSqrt(float x)
{
	union {
		float f;
		int i;
	} tmp;
	printf("%4.6f\n", tmp.f); 
	printf("%i\n", tmp.i); 
	tmp.f = x;
	printf("%4.6f\n", tmp.f); 
	printf("%i\n", tmp.i); 
	tmp.i = 0x5f3759df - (tmp.i >> 1);
	printf("%4.6f\n", tmp.f); 
	printf("%i\n", tmp.i); 
	float y = tmp.f;
	return y * (1.5f - 0.5f * x * y * y);
}

void usage(char *name)
{
    printf("Usage for program %s\n", name);
    printf("1 arguments required: 1) the x to be inverse squared.\n");
}

int main(int argc, char *argv[])
{
    if(argc!=2) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
	float x=atof(argv[1]);
	printf("x=%4.6f;xisqrt=%4.6f\n", x, InvSqrt(x));
	return 0;
}
