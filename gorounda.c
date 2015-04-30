/* go around an array:
 * self avoiding, of course,. too trivial otherwise
 * in this way you are able to compare each element of 
 * an array with all the other elements.
 * in circular fashion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define n 4
#define FLAG unsigned char /* some time also called a boolean */

typedef struct  /* optstruct, a container struct for the options */
{
    FLAG gflg;
} optstruct;

void usage(char *pname)
{
    printf("Program \"%s\" demonstrates going around an array in circular order\n", pname);
    printf("while self-avoiding. This allows comparing each member of an array with every other\n");
    printf("Usage: no arguments, produces this help text. Argument \"-g\" means \"go!\", as in carry out procedure.\n");
}

int catchopts(optstruct *opts, int argc, char **argv)
{
    int index, c;
    opterr = 0;

    while ((c = getopt (argc, argv, "g")) != -1)
        switch (c) {
            case 'g':
                opts->gflg = 1;
                break;
            case '?':
                if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                return 1;
            default:
                usage(argv[0]);
        }

    for (index = optind; index < argc; index++)
        printf ("Non-option argument %s\n", argv[index]);

    return 0;
}

int main(int argc, char *argv[])
{
    if(argc==1) {
        usage(argv[0]);
        exit(EXIT_SUCCESS);
    }
    optstruct opts={0};
    catchopts(&opts, argc, argv);

    if(opts.gflg) {

        int i, j;
        char a[n];
        /* assign a an array with first few capital letters */
        for(i=0;i<n;++i) 
            a[i]=i+65;

        /* let's have a look at the number sequence */
        printf("Self-avoiding index sequence:\n"); 
        for(i=0;i<n;++i) {
            printf("%d) ", i);
            for(j=(i+1)%n;j!=i;j=j+1-(j+1)*((j+1)/n))
                printf("%d ", j);
            printf("\n");
        }
        printf("\n"); 

        /* and now .. to finish off, the array itself */
        printf("We have the following array: "); 
        for(i=0;i<n;++i) 
            printf((i!=n-1)? "%c ": "%c.\n", a[i]);
        printf("Let's now compare each element with every other:\n"); 
        for(i=0;i<n;++i) {
            for(j=(i+1)%n;j!=i;j=j+1-(j+1)*((j+1)/n))
                printf("%cw/%c ", a[i], a[j]);
            printf("\n");
        }
    }

    return 0;
}
