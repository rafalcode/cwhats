#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(i=((b)-(c));i<(b);++i) \
            (a[i].ch)=NULL; \
    }

typedef struct
{
   char *ch;
   int csz;
} charsz_t;

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
    charsz_t *ca=malloc(cabf*sizeof(charsz_t));
    for(i=0;i<cabf;++i) ca[i].ch=NULL;

	if(tk ==NULL) {
		printf("First strtok returned NULL\n"); 
	} else {
        CONDREALLOC(casz, cabf, GBUF, ca, charsz_t);
        j=0; while(tk[j++]);
        ca[casz].csz=j;
        ca[casz].ch=calloc(ca[casz].csz, sizeof(char));
        j=0; while(tk[j]) { ca[casz].ch[j]=tk[j]; j++; }
        // printf("%s\n", ca[casz]);
        casz++;
		// printf("First strtok:\n%s(size=%zu)\n", tk, strlen(tk));
    }

	while( (tk=strtok(NULL, t)) != NULL) {
        CONDREALLOC(casz, cabf, GBUF, ca, charsz_t);
        j=0; while(tk[j++]);
        ca[casz].csz=j;
        ca[casz].ch=calloc(ca[casz].csz, sizeof(char));
        j=0; while(tk[j]) { ca[casz].ch[j]=tk[j]; j++; }
        // printf("%s\n", ca[casz]);
		// printf("%s(size=%zu)\n", tk, strlen(tk));
        casz++;
	}

    printf("Total num tokens=%i, They are as follows:\n", casz); 
    for(i=0;i<casz;++i) 
        printf("%s len=%i\n", ca[i].ch, ca[i].csz);
//    printf("\n"); 

    for(i=0;i<cabf;++i) 
        if(ca[i].ch) free(ca[i].ch);
    free(ca);

   return 0;
}
