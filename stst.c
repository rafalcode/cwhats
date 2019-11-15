/* an exercise in getline: this is the original example from the man pages
 * note that getline() does look quite convenient, because the line's memory need not
 * be explicitly allocated
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(i=((b)-(c));i<(b);++i) \
            ((a)[i]) = NULL; \
    }

typedef struct
{
    char **l;
    int lbf;
    int lsz;
} larr_t;

int main(int argc, char *argv[])
{
    FILE *stream;
    // char *line = NULL;
    size_t len = 0;
    ssize_t nread=0;
    int i, j;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int lbuf=GBUF;

    /* note we alloctae and initialize in this way, but freeing will be different:
     * it will later have to be done individually for each pointer via  for loop */
    char **aol=malloc(lbuf*sizeof(char*)); // does need this, yes, though later it won't be free'd

    /* basically here it's like creating a series of "char *tmp;" statements,
     * none equally NULL .. so valgrind will complain */
    for(i=0;i<lbuf;++i) 
        aol[i]=NULL;

    // test to see if initialised.
    for(i=0;i<lbuf;++i) 
        printf("%p ", aol+i); 
    printf("\n"); 
    int asz=0;

    while ((nread = getline(aol+asz, &len, stream)) != -1) {
        CONDREALLOC(asz, lbuf, GBUF, aol, char*);
        printf("%s", aol[asz]);
        asz++;
    }
    printf("lbuf:%i asz:%i\n", lbuf, asz);

    /* now to see if normalise works */
    for(i=asz;i<lbuf;++i)
        free(aol[i]);

    // OK now for our analysis.
    int gcou[2]={0,0}; // this is our group count.
    const int xtnt=1; // the extent of our search
    for(i=0;i<asz;++i)
        for(j=0;j<xtnt;++j) {
            if( (aol[i][j] >47) && (aol[i][j] <48) )
                gcou[1]++;
            else
                gcou[0]++;
        }

    printf("cat1: if( (aol[i][j] >47) && (aol[i][j] <48) \n");
    printf("Counts of cat0: %i, cat1 = %i\n", gcou[0], gcou[1]); 

    /* and now to free */
    for(i=0;i<asz;++i)
        free(aol[i]);
    free(aol);

    /* Ok that's it */
    fclose(stream);
    exit(EXIT_SUCCESS);
}
