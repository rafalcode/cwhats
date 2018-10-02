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
    chch_t *mou /* mouth with a tendency to eat the tail*/, *ttmp /* type temporary */;

    mou=malloc(sizeof(chch_t)); /* mouth */
    mou->c=' ';
    ttmp=mou;
    for(i=1;i<chln;++i) {
        ttmp->nc=malloc(sizeof(chch_t));
        ttmp->nc->c=' ';
        ttmp=ttmp->nc; /* with ->ncmove on */
    }
    ttmp->nc=mou;
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
        if(i>=chln) { // the "or = " was critical here.
            prt_chch(rmou);
            rmou=rmou->nc;
        }
        // printf("%c ", tmou->c); 
        tmou=tmou->nc;
        tmou->c=strng[i++];
    }
    prt_chch(rmou); // because the final one doesn't get printed
    return;
}

void roll_cchst2(chch_t *cch, size_t chln, char *strng) /* rol chain along a string */
{
    chch_t *tmou=cch;
    chch_t *rmou=cch;
    int i=0;
    do {
        if(i>=chln) { // the "or = " was critical here.
            prt_chch(rmou);
            rmou=rmou->nc;
        }
        tmou->c=strng[i++];
        tmou=tmou->nc;
    } while(strng[i]);
    prt_chch(rmou);
    return;
}

void roll_cchst3(chch_t *cch, size_t chln, char *strng) /* rol chain along a string */
{
    chch_t *trmou=NULL;
    int i=0, j;
    char seen;
    do {
        if(i>=chln-1) { // starts string one char too late if no -1
            trmou=cch;
            seen=1;
            for(j=0;j<chln;++j) {
                // printf("Comparing %c with %c\n", trmou->c, strng[i+j]);
                if(trmou->c != strng[i+j]) {
                    seen = 0;
                    // printf("break!\n"); 
                    break;
                }
                trmou=trmou->nc;
            }
            if(seen) {
                printf("match at character %i in string\n", i+1); 
            }
        }
    } while(strng[i++]);
    // final string bite check
    // nope this was not necessary ... it has got to do with the use of 
    // the forloop over the string ... see chln-1 note above
    return;
}

char cmpchch(chch_t *st1, chch_t *st2)
{
    char yes=1;
    /* temporary startpts */
    chch_t *tst1=st1, *tst2=st2;
    do {
        if(tst1->c != tst2->c) {
            yes=0;
            break;
        }
        tst1=tst1->nc;
        tst2=tst2->nc;
    } while (tst1 !=st1);
    return yes;
}

void rollcmp_cchst2(chch_t *cch, size_t chln, char *strng) /* rol chain along a string */
{
    chch_t *tmou=cch;
    chch_t *rmou=cch;
    int i=0;
    do {
        if(i>=chln) { // the "or = " was critical here.
            prt_chch(rmou);
            rmou=rmou->nc;
        }
        tmou->c=strng[i++];
        tmou=tmou->nc;
    } while(strng[i]);
    prt_chch(rmou);
    return;
}

void prtusage(void)
{
    printf("char chain tester, no args.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc!=3) {
		printf("Two args needed: subject string and target string.\n");
		exit(EXIT_FAILURE);
	}
	size_t subssz = strlen(argv[1]); // subject string size
	if(subssz > strlen(argv[2])) {
		printf("Subject string must be shorter than target string.\n");
		exit(EXIT_FAILURE);
	}

    chch_t *cch=crea_chch2(argv[1]);
    // chch_t *cch=crea_chch(3);

    /* you can roll_cchst2() with a filled in chch and it won't matter */
    roll_cchst3(cch, subssz, argv[2]);
    free_chch(cch);

    return 0;
}
