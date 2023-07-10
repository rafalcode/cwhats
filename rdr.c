/* trying to look inside an rds file
 * cannot be compressed mind you
 * abandoned, not trivial to parse into matrix fasion I'd say */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    /* declarations */
    int i, j;
    char *fn = "/mnt/sdb1/ncrepros/mayo-brain-mets/data/norm-counts/091/batch-corrected/a2.rds";
    FILE *rdin=NULL;
    // rdin = fopen(fn, "r+b");
    struct stat fsta;
    stat(fn, &fsta);
    unsigned char *buf = malloc(fsta.st_size*sizeof(unsigned char));

    rdin = fopen(fn,"rb");
    if ( fread(buf, fsta.st_size, sizeof(unsigned char), rdin) < 1 ) { /* Yup! we slurp in the baby! */
        printf("Sorry, trouble putting rds file into buffer container.\n"); 
        exit(EXIT_FAILURE);
    }

    for(i=0;i<fsta.st_size;i+=8) {
        for(j=0;j<8;++j) 
            printf("%x ", buf[8*i+j]); 
        printf("\n"); 
    }
    free(buf);

    return 0;
}
