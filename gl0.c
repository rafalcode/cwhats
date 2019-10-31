/* an exercise in getline: this is the original example from the man pages
 * note that it does lokk quite convenient, because the line's memory need not be allocated
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
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

    int lbuf=GBUF;
    char **aol=malloc(lbuf*sizeof(char*));

    // test to see if initialised.
    // for(i=0;i<lbuf;++i) 
    //     printf("%p ", aol+i); 
    // printf("\n"); 
    int asz=0;

    while ((nread = getline(aol+asz, &len, stream)) != -1) {
        CONDREALLOC(asz, lbuf, GBUF, aol, char*);
        // printf("Retrieved line of length (returned val method): %zu\n", nread);
        // printf("Retrieved line of length (strlen method): %zu\n", strlen(line));
        // fwrite(line, nread, 1, stdout);
        printf("%s", aol[asz]);
        asz++;
    }
    printf("lbuf:%i asz:%i\n", lbuf, asz);
    // aol=realloc(aol, asz*sizeof(char*)); // normalize
    for(i=0;i<lbuf;++i) {
        // free(aol[i]);
        // free(aol+i);
    }
    free(aol);
    fclose(stream);
    exit(EXIT_SUCCESS);
}
