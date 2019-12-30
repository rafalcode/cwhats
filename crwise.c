#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define GENBUF 2

typedef struct  /* optstruct, a struct for the options */
{
    unsigned char rflg, cflg; // flags for row or column wise
    int bint, eint; // beginning line, end line ... i.e. reordering done on subset of consectuive lines in a file
    int fdim, sdim; // first dimension, second dimension MxN sort of thing.
} optstruct;

int catchopts(optstruct *opstru, int oargc, char **oargv)
{
    int c;
    opterr = 0;

    while ((c = getopt (oargc, oargv, "rcb:e:f:")) != -1)
        switch (c) {
            case 'c':
                opstru->cflg = 1; break;
            case 'r':
                opstru->rflg = 1; break;
            case 'b':
                opstru->bint = atoi(optarg); break;
            case 'e':
                opstru->eint = atoi(optarg); break;
            case 'f':
                opstru->fdim = atoi(optarg); break;
            case '?':
                if((optopt == 'b') | (optopt == 'e') | (optopt == 'f'))
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
    int nclines = opstru.eint - opstru.bint;
    int leftover = nclines%opstru.fdim;
    if(leftover != 0) {
        printf("Error. Line range slice %i must be cleanly divisible by the first-dimension specified as %i.\n", nclines, opstru.fdim);
        exit(EXIT_FAILURE);
    }
    //    printf("OK. Line range slice %i matches fulldimension specification %i so we can continue.\n", nclines, fulldim);

    printf("OK. Line range slice of size %i starting rom line %i.\n", nclines, opstru.bint);

    int i, j;
    int iext= nclines/opstru.fdim;

    if((opstru.rflg) | (opstru.cflg==0)) {
        for(i=0;i<iext;++i) {
            for(j=0;j<opstru.fdim;++j) 
                printf("%i\n", j+opstru.fdim*i + opstru.bint);
        }
    } else if((opstru.rflg==0) | (opstru.cflg)) {
        for(j=0;j<opstru.fdim;++j) {
            for(i=0;i<iext;++i)
                printf("%i\n", j+opstru.fdim*i + opstru.bint);
        }
    }

    return 0;
}
