/* using fread to slup up a text file
 * now bear in mind you'll probably only want to read single word lists with this */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<sys/stat.h>

#define GBUF 64
typedef unsigned char boole;

struct chch /* chch_t: char chain, in my early code it was dcn_t */
{
    char c;
    struct chch *nc;
};
typedef struct chch chch_t;

chch_t *crea_chch(size_t chln) /* create empty ring of size chln */
{
    int i;
    chch_t *mou /* mouth with a tendency to eat the tail*/, *tai /* tail */, *ttmp /* type temporary */;

    mou=malloc(sizeof(chch_t)); /* mouth */
    mou->c=' ';
    // tai=malloc(sizeof(chch_t)); /* tail */
    // tai->c=' ';
    ttmp=mou;
    for(i=1;i<chln-1;++i) {
        ttmp->nc=malloc(sizeof(chch_t));
        ttmp->nc->c=' ';
        ttmp=ttmp->nc; /* with ->ncmove on */
    }
    ttmp->nc=mou;
    // tai->nc=mou; /* this is the vital connection, the underwater one */
    return mou;
}

chch_t *crea_chch2(char *strng) /* from a string */
{
    /* I had trouble returning to this after a few years, because I for got some elemental points:
     * don't assign temporary pointers to things that have not been directly allocated yet. I.e. only point 
     * to properly malloc'd stuff. */
    chch_t *mou=malloc(sizeof(chch_t));
    chch_t *tmou=mou; /* don't dare assign tmou to mou->nc, it has not been allocated */
    int i=0;
    mou->c=strng[i++];
    while(strng[i]) {
        tmou->nc=malloc(sizeof(chch_t));
        tmou->nc->c=strng[i++];
        tmou=tmou->nc; /* move on */
    }
    tmou->nc = mou;
    return mou;
}

void prt_chch(chch_t *cch)
{
    int i=0;
    chch_t *tmou=cch;
    do {
        putchar(tmou->c);
        tmou = tmou->nc;
        i++;
    } while (tmou != cch);
    printf(" ... %i chars\n", i); 
    return;
}

void free_chch(chch_t *mou)
{
    chch_t *st=mou->nc, *nxt;
    while (st !=mou) {
        nxt=st->nc;
        free(st);
        st=nxt;
    }
    free(mou);
}

void roll_cchst(chch_t *cch, size_t chln, char *strng) /* rol chain along a string */
{
    /* I had trouble returning to this after a few years, because I for got some elemental points:
     * don't assign temporary pointers to things that have not been directly allocated yet. I.e. only point 
     * to properly malloc'd stuff. */
    chch_t *tmou=cch;
    chch_t *rmou=cch;
    int i=0;
    tmou->c=strng[i++];
    while(strng[i]) {
        if(i>chln) {
            prt_chch(rmou);
            rmou=rmou->nc;
        }
        tmou=tmou->nc;
        tmou->c=strng[i++];
    }
    return;
}

void prtusage(void)
{
    printf("char chain tester, no args.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{

    // chch_t *cch=crea_chch2("wha");
    chch_t *cch=crea_chch(4);

    roll_cchst(cch, 4, "kavanaugh");
    free_chch(cch);

    return 0;
}
