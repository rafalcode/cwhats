/* hopefully less hilarious than hilarious exercise reading from a binary ped (bed0 file */
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
    unsigned char *indata=calloc(sz, sizeof(unsigned char));
    if ( fread(indata, sz, sizeof(unsigned char), inf) < 1 ) {
        printf("Can't read file\n");
        exit(EXIT_FAILURE);
    }
    fclose(inf);

    int i, j, cou=0;
    for(i=0;i<sz;++i) {
        printf("%x ", indata[i]); 
    }
    printf("\n"); 
    /* Ans for test.bed: 0x6c 0x1b 0x01 0xdc 0x0f 0xe7 0x0f 0x6b 0x01
     * You go across samples, for each SNP i.e. going down a column in a ped file.
     * However, the bytes used are whole for each group of sample .. if not divisible by 4
     * the final bytes will only be partially filled.
     */
    unsigned char x;
    for(i=3;i<sz;++i) {
        for(j=0;j<8;j+=2) {
            x= (indata[i]>>j)&0x03;
            printf("%x: ", x); 
            switch(x) {
                case 0x00:
                    putchar('H'); break; // homozygous on ref/ancest
                case 0x03:
                    putchar('h'); break; // homo zygous on alt
                case 0x01:
                    putchar('0'); break; // homozygous on ref/ancest
                case 0x02:
                    putchar('T'); // hetzyg
            }
            putchar(' ');
        }
    }
    /* you however need the sample numner
    printf("\n"); 

    free(indata);
    return 0;
}
