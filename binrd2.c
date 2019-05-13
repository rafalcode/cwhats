/* hopefully less hilarious than hilarious exercise reading from a binary ped (bed0 file */
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<sys/stat.h>

#define GBUF 64
/* you however need the sample number ... */

void procchunk(unsigned char *ind, int nsamps, int nby)
{
    int i, j; 
    unsigned char x;
    int loopc=0;
    // int byextent=2*
    for(i=0;i<nby;++i) {
        for(j=0;j<8;j+=2) {
            x= (ind[i]>>j)&0x03;
            // printf("%x: ", x); 
            switch(x) {
                case 0x00:
                    putchar('h'); break; // homozygous on alt/mutant (this is plink's A1, yes).
                case 0x03:
                    putchar('H'); break; // homozygous on ref/ancestral.
                case 0x01:
                    putchar('0'); break; // homozygous on ref/ancest
                case 0x02:
                    putchar('T'); // hetzyg, unphased.
            }
            putchar(' ');
            loopc++;
            if(loopc>=nsamps) {
                printf("\n"); 
                return;
            }
        }
    }
    return;
}

void prtusage(void)
{
    printf("Bed binary file reader (tester prog).\n"); 
    printf("Two args please: 1) Integer number of samples gotten beforehand 2) name of file\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if(argc != 3) {
        prtusage();
    }
    int nsamps=atoi(argv[1]);
    FILE *inf=fopen(argv[2], "rb");
    struct stat fsta;

    if ( stat(argv[2], &fsta) == -1) {
        printf("stat() unsuccessful on file.\n"); 
        exit(EXIT_FAILURE);
    }
    unsigned char *indata=calloc(fsta.st_size, sizeof(unsigned char));
    if ( fread(indata, fsta.st_size, sizeof(unsigned char), inf) < 1 ) {
        printf("Can't read file\n");
        exit(EXIT_FAILURE);
    }
    fclose(inf);

    int i, j, cou=0;
    //     printf("The hex representation:\n"); 
    //     for(i=0;i<fsta.st_size;++i) {
    //         printf("%x ", indata[i]); 
    //     }
    //     printf("\n"); 
    /* Ans for test.bed: 0x6c 0x1b 0x01 0xdc 0x0f 0xe7 0x0f 0x6b 0x01
     * You go across samples, for each SNP i.e. going down a column in a ped file.
     * However, the bytes used are whole for each group of sample .. if not divisible by 4
     * the final bytes will only be partially filled.
     */
    int nby=(int)(ceil((float)nsamps/4));
    printf("nby %i\n", nby); 
    for(i=3;i<fsta.st_size;i+=nby) {
        procchunk(indata+i, nsamps, nby);
    }

    free(indata);
    return 0;
}
