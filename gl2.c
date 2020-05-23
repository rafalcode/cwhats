/* an exercise in getline: this is the original example from the man pages
 * note that getline() does look quite convenient, because the line's memory need not
 * be explicitly allocated
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct
{
    char **l;
    size_t *lz;
    int lbf;
    int asz;
} larr_t;

int main(int argc, char *argv[])
{
    FILE *stream;
    // char *line = NULL;
    size_t len = 0;
    int i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    stream = fopen(argv[1], "r");
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

    // test to see if initialised.
    for(i=0;i<la->lbf;++i) 
        printf("%p ", la->l+i); 
    printf("\n"); 

    while ((la->lz[la->asz] = getline(la->l+la->asz, &len, stream)) != -1) {
        // nread is number of returned characters
        CONDREALLOC(la->asz, la->lbf, GBUF, la->l, char*, la->lz, size_t);
        // printf("Retrieved line of length (returned val method): %zu\n", nread);
        // printf("Retrieved line of length (strlen method): %zu\n", strlen(line));
        // fwrite(line, nread, 1, stdout);
        printf("%zu) ", la->lz[la->asz]);
        printf("%s", la->l[la->asz]);
        la->asz++;
    }
    printf("lbuf:%i asz:%i\n", la->lbf, la->asz);

    /* now to see if normalise works */
    for(i=la->asz;i<la->lbf;++i)
        free(la->l[i]);
    la->l=realloc(la->l, la->asz*sizeof(char*)); // normalize
    la->lz=realloc(la->lz, la->asz*sizeof(size_t)); // normalize

    /* and now to free */
    for(i=0;i<la->asz;++i)
        free(la->l[i]);
    free(la->l);
    free(la->lz);
    free(la);

    /* Ok that's it */
    fclose(stream);
    exit(EXIT_SUCCESS);
}
