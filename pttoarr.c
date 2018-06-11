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

int main(int argc, char *argv[])
{
    int i;
    char *tc=NULL; /* temporary char ptr */
   ca_t *c=malloc(sizeof(ca_t));
   c->sz=5;

   /* Note for clarity we're going to dereferences the pca double pointer to tc.
   It's important to malloc the pointer to the array though, havoc otherwise. */
   c->pca=malloc(sizeof(char*));
   // tc = *(c->pca);

    /* big note, you ca use the temporary pointer here, tc, or remember that in fact you should reference the double ppointers inside the struct witht he asterisk within the brackets . In the tc statement above, it doesn't matter as their is no [i] challenging for priority, but later on it does matter and causes big problems */

   /* so this single, properly allocated pointer points to an array, or a sequence of other pointers to char */
   // tc=malloc(c->sz*sizeof(char));
   (*c->pca)=malloc(c->sz*sizeof(char));
   for(i=0;i<c->sz;++i) 
       (*c->pca)[i] = (char)(i+65);
       // tc[i]=(char)(i+65);

   for(i=0;i<c->sz;++i) 
       // printf("%c ", tc[i]);
       printf("%c ", (*c->pca)[i]);
   printf("\n"); 

   // free(tc);
   free((*c->pca));
   free(c->pca);
   free(c);


   // here's all the other stuff I tried and didn't work.
//        // *(c->pca[i]) = (char)(i+65);
//        *(c->pca)[i] = (char)(i+65);
//    c->pca=malloc(c->sz*sizeof(char*));
//    for(i=0;i<c->sz;++i) 
//        // *(c->pca[i]) = (char)(i+65);
//        *(c->pca)[i] = (char)(i+65);
// 
//    for(i=0;i<c->sz;++i) 
//        printf("%c ", *(c->pca)[i]);
//    printf("\n"); 
// 
//    free(c->pca);
//    c->pca=malloc(sizeof(char*));
//    *(c->pca)=malloc(c->sz*sizeof(char));
//    for(i=0;i<c->sz;++i) 
//        *(c->pca)[i] = (char)(i+65);
// 
//    for(i=0;i<c->sz;++i) 
//        printf("%c ", *(c->pca)[i]);
//    printf("\n"); 
// 
//    free(*(c->pca));
//    free(c->pca);
//    free(c);
   return 0;
}
