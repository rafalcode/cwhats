#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 32
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(i=((b)-(c));i<(b);++i) \
            a[i]=NULL; \
    }

void prtusage(void)
{
	printf("One arg please: 1) string in FILENAME:COLUMN:SEPARATOR:COMMENTSYES:HEADERYES form\n");
	printf("Separator most probably \" \" or \",\"\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		prtusage();
    int i=0, j;
    printf("size of input string is %zu\n", strlen(argv[1]));

	char t[]="/_.";
	char *tk=strtok(argv[1], t);
    int casz=0, cabf=GBUF;
    char **ca=malloc(cabf*sizeof(char*));
    for(i=0;i<cabf;++i) ca[i]=NULL;

	if(tk ==NULL) {
		printf("First strtok returned NULL\n"); 
	} else {
        CONDREALLOC(casz, cabf, GBUF, ca, char*);
        j=0; while(tk[j++]);
        ca[casz]=calloc(j, sizeof(char));
        j=0; while(tk[j]) { ca[casz][j]=tk[j]; j++; }
        // printf("%s\n", ca[casz]);
        casz++;
		// printf("First strtok:\n%s(size=%zu)\n", tk, strlen(tk));
    }

	while( (tk=strtok(NULL, t)) != NULL) {
        CONDREALLOC(casz, cabf, GBUF, ca, char*);
        j=0; while(tk[j++]);
        ca[casz]=calloc(j, sizeof(char));
        j=0; while(tk[j]) { ca[casz][j]=tk[j]; j++; }
        // printf("%s\n", ca[casz]);
		// printf("%s(size=%zu)\n", tk, strlen(tk));
        casz++;
	}

    printf("Total num tokens=%i, They are as follows:\n", casz); 
    for(i=0;i<casz;++i) 
        printf("%s ", ca[i]);
    printf("\n"); 

    for(i=0;i<cabf;++i) 
        if(ca[i]) free(ca[i]);
    free(ca);

   return 0;
}
