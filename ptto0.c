/* assigning values to a pointer to an array
 * which is what amounts to a double pointer */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    int sz;
    char **pca; /* pointer to charaqcter array */
} ca_t;

typedef struct 
{
    int sz;
    ca_t **c; /* pointer to charaqcter array */
} aca_t;

void reall_pca(ca_t *c)
{
    c->sz=10;
    (*c->pca)=realloc((*c->pca), c->sz*sizeof(char));
    return;
}

void prt_aca(aca_t *ac)
{
    int i, j;
    for(i=0;i<ac->sz;++i) {
        printf("ac#%i: ", i);
        for(j=0;j<(*ac->c)[i].sz;j++)
            printf("%c ", (*(*ac->c)[i].pca)[j]);
        printf("\n"); 
    }
    return;
}




int main(int argc, char *argv[])
{
    int i, j;
    char *tc=NULL; /* temporary char ptr */
    ca_t *tca=NULL; /* temporary char ptr */
    aca_t *ac=malloc(sizeof(aca_t));
    ac->sz=3;
    ac->c=malloc(sizeof(ca_t*));
    (*ac->c)=malloc(ac->sz*sizeof(ca_t));
    for(i=0;i<ac->sz;++i) {
        (*ac->c)[i].sz = 5;
        (*ac->c)[i].pca = malloc(sizeof(char*));
        (*(*ac->c)[i].pca) = malloc((*ac->c)[i].sz*sizeof(char));
        for(j=0;j<(*ac->c)[i].sz;j++)
            (*(*ac->c)[i].pca)[j] =(char)(i*(*ac->c)[i].sz+j+65);
    }
    prt_aca(ac);
    /* freeing stuff */
    for(i=0;i<ac->sz;++i) {
        free((*(*ac->c)[i].pca));
        free((*ac->c)[i].pca);
    }

    free((*ac->c));
    free(ac->c);
    free(ac);

    return 0;
}
