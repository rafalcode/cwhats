#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GENBUF 2

typedef struct  /* optstruct, a struct for the options */
{
    unsigned char rflg, cflg; // flags for row or column wise
    int bint, uint; // beginning line, until line (not inclusive) ... i.e. reordering done on subset of consectuive lines in a file
    int fdim; // first dimension, second dimension MxN sort of thing.
} optstruct;

int catchopts(optstruct *opstru, int oargc, char **oargv)
{
    int c;
    opterr = 0;

    while ((c = getopt (oargc, oargv, "rcb:u:f:")) != -1)
        switch (c) {
            case 'c':
                opstru->cflg = 1; break;
            case 'r':
                opstru->rflg = 1; break;
            case 'b':
                opstru->bint = atoi(optarg); break;
            case 'u':
                opstru->uint = atoi(optarg); break;
            case 'f':
                opstru->fdim = atoi(optarg); break;
            case '?':
                if((optopt == 'b') | (optopt == 'u') | (optopt == 'f'))
                    fprintf (stderr, "Option -%c requires an integer argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                abort();
        }

    return 0;
}

void prthlp(void)
{
    printf("Option-catching test program. First two arguments are, however, ignored.\n"); 
    return;
}

int main (int argc, char **argv)
{
    optstruct opstru={0};
    int argignore=0; // note unistd's opthandlign will ignore ht first argument, as it may be the execuable.
    int oargc=argc-argignore;
    char **oargv=argv+argignore;
    catchopts(&opstru, oargc, oargv);
    // printf ("Vals: rflag = %d, cflag = %d, bint = %i, eint = %i, fdim = %i, sdim = %i\n", opstru.rflg, opstru.cflg, opstru.bint, opstru.eint, opstru.fdim, opstru.sdim);
    int nclines = opstru.uint - opstru.bint;
    int leftover = nclines%opstru.fdim;
    if(leftover != 0) {
        printf("Error. Line range slice %i must be cleanly divisible by the first-dimension specified as %i.\n", nclines, opstru.fdim);
        exit(EXIT_FAILURE);
    }
    //    printf("OK. Line range slice %i matches fulldimension specification %i so we can continue.\n", nclines, fulldim);

    printf("OK. Line range slice of size %i starting rom line %i.\n", nclines, opstru.bint);

    int i, j;
    // int iext, othdim= nclines/opstru.fdim /* other, as in, second, dimension */;
    int iext= nclines/opstru.fdim /* other, as in, second, dimension */;
    // if((opstru.rflg) & (opstru.cflg==0))
    //     iext= nclines/othdim;
    // else if((opstru.rflg==0) & (opstru.cflg))
    //     iext= othdim;

    /* need an array which is columnwise if transformation is to row-wise, and vice versa */
    int *arr=malloc(nclines*sizeof(int));
    int k=0;
    if((opstru.rflg==0) & (opstru.cflg)) {
        for(i=0;i<iext;++i) {
            for(j=0;j<opstru.fdim;++j) 
                // arr[j+opstru.fdim*i] = k++ + opstru.bint;
                arr[k++] = j+opstru.fdim*i + opstru.bint;
        }
    } else if((opstru.rflg) & (opstru.cflg==0)) {
        for(j=0;j<opstru.fdim;++j) {
            for(i=0;i<iext;++i)
                // arr[j+opstru.fdim*i] = k++ + opstru.bint;
                arr[k++] = j+opstru.fdim*i + opstru.bint;
        }
    }

    /* original order is */
    printf("Original order is:\n");
    for(i=0;i<nclines;++i) 
        printf("%i\n", arr[i]); 

    /* now print out , note how the order is opposite to defining the array */
    printf("New order is:\n");
    if((opstru.rflg) & (opstru.cflg==0)) {
        for(i=0;i<iext;++i) {
            for(j=0;j<opstru.fdim;++j) 
                // printf("%i\n", j+opstru.fdim*i + opstru.bint);
                printf("%i\n", arr[j+opstru.fdim*i]);
        }
    } else if((opstru.rflg==0) & (opstru.cflg)) {
        for(j=0;j<opstru.fdim;++j) {
            for(i=0;i<iext;++i)
                // printf("%i\n", j+opstru.fdim*i + opstru.bint);
                printf("%i\n", arr[j+opstru.fdim*i]);
        }
    }

    free(arr);

    return 0;
}
