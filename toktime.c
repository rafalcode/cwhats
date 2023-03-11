/* adapting tok0 for time points */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct /* time point type, tp_t */
{
    int h, m, s, hh;
} tp_t;

tp_t *s2tp2(char *str)
{
    tp_t *p=calloc(1, sizeof(tp_t));
    int rawns[4]={0};
	char tok[]=":.";
    int cou=0;

    // let's start
	char *tk=strtok(str, tok);
	if(tk ==NULL) {
		printf("strtok returned NULL, deault is seconds.\n");
        p->s=atoi(str);
        return p;
	} else {
		printf("First strtok: \"%s\" (size=%zu)\n", tk, strlen(tk));
        rawns[cou++]=atoi(tk);
    }
	while( (tk=strtok(NULL, tok)) != NULL) {
        if(cou>3) {
            printf("Time is malformed if it has so many [:.] tokens\n"); 
            exit(EXIT_FAILURE);
        }
		printf("\"%s\" (size=%zu)\n", tk, strlen(tk));
        rawns[cou++]=atoi(tk);
    }
    if(cou==2) {
        p->s=rawns[0];
        p->hh=rawns[1];
    } else if (cou==3) {
        p->m=rawns[0];
        p->s=rawns[1];
        p->hh=rawns[2];
    } else if (cou==4) {
        p->h=rawns[0];
        p->m=rawns[1];
        p->s=rawns[2];
        p->hh=rawns[3];
    }
    return p;
}

int main(int argc, char *argv[])
{
    if(argc != 2) {
        printf("Need 1 arg, a timepoint in hours:mins:secs.hh style\n"); 
        exit(EXIT_FAILURE);
    }
    tp_t *p=s2tp2(argv[1]);
    printf("hours=%i minutes=%i seconds=%i hundreths=%i\n", p->h, p->m, p->s, p->hh); 

    free(p);
   return 0;
}
