/* an exercise in getline: this is the original example from the man pages
 * note that getline() does look quite convenient, because the line's memory need not
 * be explicitly allocated
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(i=((b)-(c));i<(b);++i) \
            ((a)[i]) = NULL; \
    }

typedef struct  /* optstruct, a struct for the options */
{
    unsigned char rflg, cflg; // flags for row or column wise
    char *input; // beginning line, end line ... i.e. reordering done on subset of consectuive lines in a file
    int bint, uint; // beginning line, end line ... i.e. reordering done on subset of consectuive lines in a file
    int m; // aka nrows, maths-style
    int n; // aka ncols, maths-style
} optstruct;

int catchopts(optstruct *opstru, int oargc, char **oargv)
{
    int c;

    while ((c = getopt (oargc, oargv, "b:u:m:n:i:")) != -1)
        switch (c) {
            case 'i':
                opstru->input = optarg; break;
            case 'b':
                opstru->bint = atoi(optarg)-1; break; // note we convert to zero-index here
            case 'u':
                opstru->uint = atoi(optarg); break; // no conversion because it's uninclusive
            case 'm':
                opstru->m = atoi(optarg); break;
            case 'n':
                opstru->n = atoi(optarg); break;
            case '?':
                if((optopt == 'b') | (optopt == 'u') | (optopt == 'm') | (optopt == 'n') |  (optopt == 'i'))
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
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

void prtusage(void)
{
    printf("glord: rearranges a certain line range of a specified input file from columnwise to rowwise and vice versa\n");
    printf("example usage: ./glord -i m3.txt -r -b 1 -u 6 -f 2\n");
    printf("this would take line 1 to line 6 (allinclusive) of file m3.txt and render it row-wise if it were columnwise.\n");
    printf("-f is hte first dimension of the required wise-ness. In this case lines 1 to 6 would be originally 3 rows, but will turn to 2, so -f 2\n");
    printf("Beware files with more than one range that has to be rearranged! You need to multiple passes through this program, modifying -b and -u as you go on.\n");
    printf("example: second range of column wise8x12 section: glord -i gord.txt -r -b 97 -u 192 -f 12\n"); 
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        // fprintf(stderr, "Usage: %s -i <file> -r/c (flag for row or column) -b firstline -e lastline -f firstdimension\n", argv[0]);
        // fprintf(stderr, "note:  use -r option if range colwise and you want row-wise, and vice versa.\n");
        prtusage();
        exit(EXIT_FAILURE);
    }

    optstruct opstru={0};
    int argignore=0; // note unistd's opthandlign will ignore ht first argument, as it may be the execuable.
    int oargc=argc-argignore;
    char **oargv=argv+argignore;
    catchopts(&opstru, oargc, oargv);

    /* some initial tests on our input values */
    int nclines = opstru.uint - opstru.bint;
    int leftover = nclines%opstru.m;
    if(leftover != 0) {
        printf("Error. Line range slice %i must be cleanly divisible by the first-dimension specified as %i.\n", nclines, opstru.m);
        exit(EXIT_FAILURE);
    }
#ifdef DBG
    else
        printf("OK. Line range slice %i is cleanly divisible by the first-dimension specified as %i.\n", nclines, opstru.m);
#endif
    int ncols = nclines/opstru.m;
    if(ncols != opstru.n) {
        printf("Error. until-line minus beginningline over -m option = %i must equal -n option which is %i.\n", ncols, opstru.n);
        exit(EXIT_FAILURE);
    }

    /*OK, let's turn our attention to reading the file */
    size_t len = 0;
    ssize_t nread=0;
    int i, j;

    FILE *stream = fopen(opstru.input, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int lbuf=GBUF;

    /* note we allocate and initialize in this way, but freeing will be different:
     * it will later have to be done individually for each pointer via  for loop */
    char **aol=malloc(lbuf*sizeof(char*)); // does need this, yes, though later it won't be free'd
    /* following keeps valgrind quiet */
    for(i=0;i<lbuf;++i) 
        aol[i]=NULL;

#ifdef DBG
    // test to see if initialised.
    for(i=0;i<lbuf;++i) 
        printf("%p ", aol+i); 
    printf("\n"); 
#endif

    int asz=0;

    while ((nread = getline(aol+asz, &len, stream)) != -1) {
        CONDREALLOC(asz, lbuf, GBUF, aol, char*);
#ifdef DBG
        printf("%s", aol[asz]);
#endif
        asz++;
    }
#ifdef DBG
    printf("lbuf:%i asz:%i\n", lbuf, asz);
#endif

    /* We're almost finished reading the line in ... just need to normalize */
    for(i=asz;i<lbuf;++i)
        free(aol[i]);

    int *arr2=malloc(nclines*sizeof(int));
    int *arr3=malloc(nclines*sizeof(int));
    for(i=0;i<opstru.m;++i)
        for(j=0;j<opstru.n;++j)
            arr2[i*opstru.n+j] = j*opstru.m+i; 
    /* rev */
    for(i=0;i<opstru.m;++i)
        for(j=0;j<opstru.n;++j)
            arr3[arr2[i*opstru.n+j]] = i*opstru.n+j;

    /* print the first un-rearranged section, if any */
    for(i=0;i<opstru.bint;++i) 
        printf("%s", aol[i]);

    for(i=0;i<opstru.m;++i) 
        for(j=0;j<opstru.n;++j)
            printf("%s", aol[arr2[i*opstru.n+j]]); 

    /* and now the last part */
    for(i=opstru.uint;i<asz;++i) 
        printf("%s", aol[i]);

    /* and now to free */
    for(i=0;i<asz;++i)
        free(aol[i]);
    // free(aol); // not required
    free(arr2);
    free(arr3);

    /* Ok that's it */
    fclose(stream);
    exit(EXIT_SUCCESS);
}
