/* using fread to slup up a text file
 * now bear in mind you'll probably only want to read single word lists with this */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<sys/stat.h>

#define GBUF 64

void prtusage(void)
{
    printf("quick text file slurper using fread.\n"); 
	printf("One args please: 1) Integer number of bytes you want to read 2) name of file\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		prtusage();
    }

	struct stat ifsta;
	if(stat(argv[1], &ifsta) == -1) {
		fprintf(stderr, "Problem with argument 1: Can't ifstat input file %s", trueopts->inpfn);
		exit(EXIT_FAILURE);
	}

    FILE *inf=fopen(argv[1], "r");
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
