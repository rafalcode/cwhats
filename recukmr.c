/* Generating kmers via recursion
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SYMBASZ 4 // symbol array size, you will need to change this

char **tostr(char c, char **s, int totimes, int vtimes, int *k)
{
    /* overall the issue is, we need to return a string */
    s[*k][totimes-vtimes]=c;
    return s;
}

void recurseme(char *a, int asz, int totimes, int vtimes, char **s, int *k, int totkm)
{
    int i, j;
    if(vtimes > 0)
        for(i=0;i<asz;++i)
            recurseme(a, asz, totimes, vtimes-1, tostr(a[i], s, totimes, vtimes, k), k, totkm);
    else {
        /* we need to prepare the next string, because recursion overwrites its own string
         * which would be fine, but we need to retain it as we storing all the kmwers */
        if(*k < totkm-1)
            for(j=0;j<totimes-1;++j) // avoid strcpy for short strings
                s[(*k)+1][j] = s[*k][j];
        (*k)++;
    }
   return;
}

void prtusage(void)
{
    printf("Generates N recursive for-loops for the range of nucleotides (i.e. range of 4).\n"); 
    printf("You need to give an integer N as argument.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc == 1) {
		prtusage();
		exit(EXIT_FAILURE);
	}
    int i;
    int totimes /* the fixed value */, vtimes /* the variable value, which will follow the recursion tree */;
    totimes=vtimes=atoi(argv[1]);

    /* hard-coded */
    char a[SYMBASZ]={'A', 'C', 'G', 'T'};
    int totkm=pow(SYMBASZ, totimes);
    char **s=malloc(totkm*sizeof(char*));
    for(i=0;i<totkm;++i) 
        s[i]=calloc(totimes+1, sizeof(char));

    int k=0;
    recurseme(a, SYMBASZ, totimes, vtimes, s, &k, totkm);

    if(totimes<7) {
        for(i=0;i<totkm;++i) 
            printf("%s ", s[i]);
        printf("\n");
        printf("Those were the %i %i-mers.\n", totkm, totimes); 
    } else
        printf("There were %i %i-mers, but too many to print.\n", totkm, totimes); 

    for(i=0;i<totkm;++i) 
        free(s[i]);
    free(s);

   return 0;
}
