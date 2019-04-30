#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
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

	char t[]=":";
	char *tk=strtok(argv[1], t);
    int casz=0, cabf=GBUF;
    char **ca=malloc(cabf*sizeof(char*));

	if(tk ==NULL) {
		printf("strtok returned NULL\n"); 
	} else {
        CONDREALLOC(casz, cabf, GBUF, ca, char*);
        ca[casz++]
		printf("First strtok:\n%s(size=%zu)\n", tk, strlen(tk));
    }

	while( (tk=strtok(NULL, t)) != NULL) {
		printf("%s(size=%zu)\n", tk, strlen(tk));
	}

   return 0;
}
