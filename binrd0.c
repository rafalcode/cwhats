/* hilarious exercise reading from a binary ped (bed0 file */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<sys/stat.h>

#define GBUF 64

void prtusage(void)
{
    printf("Binary file reader\n"); 
	printf("Two args please: 1) Integer number of bytes you want to read 2) name of file\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc != 3) {
		prtusage();
    }
    int sz=atoi(argv[1]);
    FILE *inf=fopen(argv[2], "rb");
    char *indata=calloc(sz+1, sizeof(char));
    if ( fread(indata, sz, sizeof(char), inf) < 1 ) {
        printf("Can't read file\n");
        exit(EXIT_FAILURE);
    }
    fclose(inf);

    int i, cou=0;
    for(i=0;i<sz;++i) {
        printf("%u ", (unsigned)indata[i]); 
        if(127<(unsigned)indata[i])
            cou++;
    }
    printf("\n"); 
    printf("#vals over 127 was %i\n", cou);
    if(!cou)
        printf("Read chars were:\n%s\n", indata); 

    free(indata);
    return 0;
}
