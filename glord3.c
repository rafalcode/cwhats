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
#define CONDREALLOC(x, b, c, a, t, a2, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        for(i=((b)-(c));i<(b);++i) { \
            ((a)[i]) = NULL; \
            ((a2)[i]) = 0; \
        } \
    }

typedef struct  /* optstruct, a struct for the options */
{
    char *input; // beginning line, end line ... i.e. reordering done on subset of consectuive lines in a file
    int bint, uint; // beginning line, end line ... i.e. reordering done on subset of consectuive lines in a file
    int m; // aka nrows, maths-style
    int n; // aka ncols, maths-style
    int c; // aka the new ncols
} optstruct;

typedef struct /* larr_t */
{
    char **l; 
    unsigned *lz;
    int lbf;
    int asz;
} larr_t;

int catchopts(optstruct *opstru, int oargc, char **oargv)
{
    int c;
    opterr = 0;

    while ((c = getopt (oargc, oargv, "c:b:u:m:n:i:")) != -1)
        switch (c) {
            case 'i':
                opstru->input = optarg; break;
            case 'b':
                // the beginning row ... i.e. when you want re-arranging to start at
                opstru->bint = atoi(optarg)-1; break; // note we convert to zero-index here
            case 'u':
                // the until row ... i.e. when you want re-arranging to end at
                opstru->uint = atoi(optarg); break; // no conversion because it's uninclusive
            case 'c':
                // the new requested ncols
                opstru->c = atoi(optarg); break;
            case 'm':
                // original nrows
                opstru->m = atoi(optarg); break;
            case 'n':
                // original ncols
                opstru->n = atoi(optarg); break;
            case '?':
                if((optopt == 'b') | (optopt == 'u') | (optopt == 'm') | (optopt == 'n') | (optopt == 'i') | (optopt == 'c'))
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

larr_t *slurplines(char *fn)
{
    FILE *stream;
    // char *line = NULL;
    size_t len = 0;
    int i;

    stream = fopen(fn, "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    larr_t *la=malloc(sizeof(larr_t));
    la->lbf=GBUF;
    la->asz=0;
    la->l=malloc(la->lbf*sizeof(char*)); // does need this, yes, though later it won't be free'd
    la->lz=malloc(la->lbf*sizeof(size_t)); // does need this, yes, though later it won't be free'd
    for(i=0;i<la->lbf;++i) {
        la->lz[i]=0;
        la->l[i]=NULL;
    }

    while ((la->lz[la->asz] = getline(la->l+la->asz, &len, stream)) != -1) {
        // nread is number of returned characters
        CONDREALLOC(la->asz, la->lbf, GBUF, la->l, char*, la->lz, size_t);
        // printf("Retrieved line of length (returned val method): %zu\n", nread);
        // printf("Retrieved line of length (strlen method): %zu\n", strlen(line));
        // fwrite(line, nread, 1, stdout);
        if(la->l[la->asz][la->lz[la->asz]-1]=='\n') // check the newline
            la->l[la->asz][la->lz[la->asz]-1]='\0'; // smash the newline, of course you could save a byte and reallocate, etc. etc.
        la->asz++;
    }

    /* now to see if normalise works */
    for(i=la->asz;i<la->lbf;++i)
        free(la->l[i]);
    la->l=realloc(la->l, la->asz*sizeof(char*)); // normalize
    la->lz=realloc(la->lz, la->asz*sizeof(size_t)); // normalize

    /* Ok that's it */
    fclose(stream);
    return la;
}

void prtdbg(larr_t *la)
{
    int i;
    printf("No. of lines read using getline() is %i\n", la->asz); 
    for(i=0;i<la->asz;++i) {
        printf("LZ=%u, LINEITSELF=%s", la->lz[i], la->l[i]); 
        printf("\n"); // just to prove that newline were smashed.
    }
}

void prtasmat(larr_t *la, int *arr2, int m, int n, int b, int u)
{
    int i, j;

    /* 1. print the first un-rearranged section, if any */
    for(i=0;i<b;++i) 
        printf((i==b-1)?"%s\n":"%s ", la->l[i]);

    /* 2. now re-arrange into column-wise */
    // int woff; // with offset due to b
    for(i=0;i<m;++i) {
        // woff=b+arr2[i*n+j];
        for(j=0;j<n;++j)
            printf((j==n-1)?"%s\n":"%s ", la->l[b+arr2[i*n+j]]); 
    }

    /* 3. and now the last un-rearranged part */
    for(i=u;i<la->asz;++i) 
        printf((i==la->asz-1)?"%s\n":"%s ", la->l[i]);

    return;
}

void prtrearr(larr_t *la, int *arr2, int m, int n, int b, int u)
{
    int i, j;

    /* 1. print the first un-rearranged section, if any */
    for(i=0;i<b;++i) 
        printf("%s\n", la->l[i]);

    /* 2. now re-arrange into column-wise */
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
            printf("%s\n", la->l[b+arr2[i*n+j]]); 

    /* 3. and now the last un-rearranged part */
    for(i=u;i<la->asz;++i) 
        printf("%s\n", la->l[i]);

    return;
}

void prtrearrl(larr_t *la, int *arr2, int m, int n, int b, int u) /* print as line */
{
    int i, j;

    /* 1. print the first un-rearranged section, if any */
    for(i=0;i<b;++i) 
        printf("%s ", la->l[i]);

    /* 2. now re-arrange into column-wise */
    for(i=0;i<m;++i)
        for(j=0;j<n;++j)
            printf("%s ", la->l[b+arr2[i*n+j]]); 

    /* 3. and now the last un-rearranged part */
    if(u < la->asz-1) {
        for(i=u;i<la->asz;++i) 
            printf((i==la->asz-1)?"%s\n":"%s ", la->l[i]);
    } else
        printf("\n");

    return;
}

void prtusage(void)
{
    printf("glord3: rearranges a certain line range of a specified input file from columnwise to rowwise and vice versa\n");
    // printf("example usage: ./glord -i m3.txt -r -b 1 -u 6 -f 2\n");
    printf("example usage: ./glord3 -i m3.txt -b 1 -u 6 -n 12\n");
    // printf("this would go from the first line (-b 1) until the sixth line (-u 6) of file m3.txt and render it row-wise if it were columnwise.\n");
    printf("this would go from the first line (-b 1) until the sixth line (-u 6) of file m3.txt and tranpsoe to rows with 12 columns per row.\n");
    // printf("-f is hte first dimension of the required wise-ness. In this case lines 1 to 6 would be originally 3 rows, but will turn to 2, so -f 2\n");
    // printf("Beware files with more than one range that has to be rearranged! You need to multiple passes through this program, modifying -b and -u as you go on.\n");
    // printf("example: second range of column wise8x12 section: glord -i gord.txt -r -b 97 -u 192 -f 12\n"); 
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if (argc == 1) {
        // fprintf(stderr, "Usage: %s -i <file> -b firstline -e lastline -m numrows -n numcols\n", argv[0]);
        // fprintf(stderr, "note:  use -r option if range colwise and you want row-wise, and vice versa.\n");
        prtusage();
        exit(EXIT_FAILURE);
    }
    int i, j;
    optstruct opstru={0};
    int argignore=0; // note unistd's opthandlign will ignore ht first argument, as it may be the execuable.
    int oargc=argc-argignore;
    char **oargv=argv+argignore;
    catchopts(&opstru, oargc, oargv);

    /* some initial tests on our input values */
    int nclines = opstru.uint - opstru.bint;
    int nrows = nclines/opstru.n; // number of rows
    int remr = nclines%opstru.n; // number of remainder ... will give error.
    if(remr) {
        printf("Error: number of cols must divide -b to -u range evenly\n"); 
        exit(EXIT_FAILURE);
    }

    larr_t *la=slurplines(opstru.input);
    if(la->asz < opstru.uint) {
        printf("Error: input file does not have enough lines for your requested layout\n");
        exit(EXIT_FAILURE);
    }

    /* so, it's original column-wise: */
    int *arr2=malloc(nclines*sizeof(int));
    for(j=0;j<nrows;++j)
        for(i=0;i<opstru.n;++i)
            arr2[j*opstru.n+i] = j+nrows*i; 

    // /* arr3, the transposition */
    // int *arr3=malloc(nclines*sizeof(int));
    // for(i=0;i<nrows;++i)
    //     for(j=0;j<opstru.n;++j)
    //         arr3[j*nrows+i] = arr2[i*opstru.n+j];
    // printf("Arr3:\n"); 
#ifdef DBG
    printf("Arr2:\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<opstru.n;++j)
            printf("%i ", arr2[i*opstru.n+j]); 
    printf("\n"); 
    for(i=0;i<nrows;++i)
        for(j=0;j<opstru.n;++j)
            printf("%s ", la->l[opstru.bint+arr2[i*opstru.n+j]]); 
    printf("\n"); 
#endif

    for(i=0;i<opstru.bint;++i)
        printf("%s\n", la->l[i]);

    int nfrows = nclines/opstru.c;
    for(i=0;i<nfrows;++i)
        for(j=0;j<opstru.c;++j)
            printf("%s\n", la->l[opstru.bint+arr2[i*opstru.c+j]]);

    int leftover = nclines%opstru.c;
    if(leftover)
        for(j=0;j<leftover;++j)
            printf("%s\n", la->l[opstru.bint+arr2[i*opstru.c+j]]);

    /* and now to free */
    for(i=0;i<la->asz;++i)
        free(la->l[i]);
    free(la->l);
    free(la->lz);
    free(la);
    free(arr2);
    // free(arr3);

    /* Ok that's it */
    exit(EXIT_SUCCESS);
}
