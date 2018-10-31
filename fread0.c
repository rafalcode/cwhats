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

typedef struct /* ia_t, index array type */
{
    unsigned **i /* indices */, bf /* buffer for size value*/ , sz /* final unoccupied index aka size */;
} ia_t;

chch_t *crea_chch(size_t chln) /* create empty ring of size chln */
{
    int i;
    chch_t *mou /* mouth with a tendency to eat the tail*/, *tai /* tail */, *ttmp /* type temporary */;

    mou=malloc(sizeof(chch_t)); /* mouth */
    mou->c='\0';
    tai=malloc(sizeof(chch_t)); /* tail */
    tai->c='\0';
    ttmp=mou;
    for(i=1;i<chln-1;++i) {
        ttmp->nc=malloc(sizeof(chch_t));
        ttmp->nc->c='\0';
        ttmp=ttmp->nc; /* with ->ncmove on */
    }
    ttmp->nc=tai;
    tai->nc=mou; /* this is the vital connection, the underwater one */
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

void roll_cchst(chch_t *cch, size_t chln, char *strng) /* rol chain along a string */
{
    /* I had trouble returning to this after a few years, because I for got some elemental points:
     * don't assign temporary pointers to things that have not been directly allocated yet. I.e. only point 
     * to properly malloc'd stuff. */
    chch_t *tmou=cch;
    int i=0;
    tmou->c=strng[i++];
    while(strng[i]) {
        putchar(tmou->c);
        tmou=tmou->nc;
        tmou->c=strng[i++];
        putchar(' ');
    }
    putchar('\n');
    return;
}

void prt_chch(chch_t *cch)
{
    putchar(cch->c);
    chch_t *tmou= cch->nc;
    while(tmou != cch) {
        putchar(tmou->c);
        tmou = tmou->nc;
    }
    putchar('\n');
    return;
}

// boole roll_chch(chch_t *cch, char *strng)
// {
//     boole ret=1;
//     boole matchyes=0;
//     chch_t *tmou= cch;
//     while(strng[i]) {
//         while {
//             if(!matchyes) {
//                 ZZ
// 
//         } (tmou !=mou)
//         ifputchar(tmou->c);
//         tmou = tmou->nc;
//     }
//     putchar('\n');
// 
// }

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

ia_t *crea_ia(void)
{
    ia_t *ia=malloc(sizeof(ia_t));
    ia->bf=GBUF;
    ia->sz=0;
    ia->i=malloc(sizeof(unsigned*));
    (*ia->i)=malloc(ia->bf*sizeof(unsigned));
    return ia;
}

void reall_ia(ia_t *ia)
{
    ia->bf += GBUF;
    (*ia->i)=realloc((*ia->i), ia->bf*sizeof(unsigned));
    return;
}

void free_ia(ia_t *ia)
{
    free((*ia->i));
    free(ia->i);
    free(ia);
    return;
}

void norm_ia(ia_t *ia)
{
    (*ia->i)=realloc((*ia->i), ia->sz*sizeof(unsigned));
    return;
}

void naiveprt_txtia(char *txt, ia_t *ia)
{
    /* the most naive print */
    int i, j;
    /* first line needs special treatment */
    for(j=0; j<=(*ia->i)[0]; j++)
        putchar(txt[j]);
    /* rest can be done in a loop though beware if final character is not a newline .. they usually are */
    for(i=1;i<ia->sz;i++) {
        for(j=(*ia->i)[i-1]+1; j<=(*ia->i)[i]; j++)
            putchar(txt[j]);
    }
    return;
}

void prtusage(void)
{
    printf("quick text file slurper using fread.\n"); 
	printf("One args please: 1) Integer number of bytes you want to read 2) name of file\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc != 2) {
		prtusage();
    }

	struct stat ifsta;
	if(stat(argv[1], &ifsta) == -1) {
		fprintf(stderr, "Problem with argument 1: Can't ifstat input file %s", argv[1]);
		exit(EXIT_FAILURE);
	}

    FILE *inf=fopen(argv[1], "r");
    char *txt=calloc(ifsta.st_size, sizeof(char));
    if ( fread(txt, ifsta.st_size, sizeof(char), inf) < 1 ) {
        printf("%s file can be ifstat'd, but isn't being read properly.\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    fclose(inf);

    int i, cou=0;
    ia_t *ia=crea_ia();
    for(i=0;i<ifsta.st_size;++i) {
        if(txt[i] == '\n') {
            if(ia->sz == ia->bf-1)
                reall_ia(ia);
            (*ia->i)[cou++] = i;
            ia->sz = cou;
        }
    }
    norm_ia(ia);

    for(i=0;i<ia->sz;++i) 
        printf("%i ", (*ia->i)[i]);
    printf("\n"); 

    naiveprt_txtia(txt, ia);

    free_ia(ia);
    free(txt);

    // chch_t *cch=crea_chch(5);
    chch_t *cch=crea_chch2("wha");
    prt_chch(cch);

    roll_cchst(cch, 3, "kavanaugh");
    free_chch(cch);

    return 0;
}
