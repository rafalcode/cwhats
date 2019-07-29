#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define GBUF 2
#define MAXTAB 5
#define MAXCPT 10 // max customers per table
#define TOTCUSTS 20 // total customers to process
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }
#define CONDREALLOC2(x, b, c, a1, a2, t1, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
    }
#define CONDREALLOC3(x, b, c, a1, a2, a3, t1, t2, t3); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        (a3)=realloc((a3), (b)*sizeof(t3)); \
        memset(((a3)+(b)-(c)), 1, (c)*sizeof(t3)); \
    }
// had to craft that memset up there carefully
#define CONDREALLOC4(x, b, c, a1, a2, a3, a4, t1, t2, t3, t4); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
        (a3)=realloc((a3), (b)*sizeof(t3)); \
        memset(((a3)+(b)-(c)), 1, (c)*sizeof(t3)); \
        (a4)=realloc((a4), (b)*sizeof(t4)); \
    }

typedef struct /* a_c, array container */
{
    int gbuf, asz;
    int *a, *mx;
    float *af;
    unsigned char *msk;
} a_c;

float normrand(float mu, float sigma)
{
    float U1, U2, W, mult;
    static float X1, X2;
    static int call = 0;

    if (call == 1) {
        call = !call;
        return (mu + sigma * (float) X2);
    }
    /* Marsaglia and Bray method */
    do {
        U1 = -1 + ((float) rand () / RAND_MAX) * 2;
        U2 = -1 + ((float) rand () / RAND_MAX) * 2;
        W = pow (U1, 2) + pow (U2, 2);
    } while (W >= 1 || W == 0);

    mult = sqrt ((-2 * log (W)) / W);
    X1 = U1 * mult;
    X2 = U2 * mult;

    call = !call;

    return (mu + sigma * (float) X1);
}

void probme(void) /* version with mask */
{
    /* OK, so this won't be that easy. the full table needs to be taken out of the probability
     * line. Best way is a mask, topen, which, if 0, will be ignored */
    int i, gbuf=GBUF;
    a_c *ac=malloc(sizeof(a_c));
    ac->gbuf=GBUF;
    ac->a=calloc(ac->gbuf, sizeof(int));
    ac->mx=calloc(ac->gbuf, sizeof(int));
    ac->af=malloc(ac->gbuf*sizeof(float));
    ac->msk=malloc(ac->gbuf*sizeof(unsigned char));
    memset(ac->msk, 1, gbuf*sizeof(unsigned char));
    ac->mx=malloc(ac->gbuf*sizeof(unsigned char));
    for(i=0;i<ac->gbuf;++i) 
        ac->mx[i] = (int)(0.5+normrand(6, 1));
    ac->asz=1;
    int tsum;
    float tf;
    int choseni;
    float pn;
    int ncusts=0;

    do {
        tsum=1;
        for(i=1;i<ac->asz;++i)
            if(ac->msk[i])
                tsum += ac->a[i];
        ac->af[0]=1.0/tsum; // notional prob of this empty table (the waiting next)
        tf=ac->af[0];
        for(i=1;i<ac->asz;++i)
            if(ac->msk[i]) {
                ac->af[i]=tf+(float)ac->a[i]/tsum;
                tf=ac->af[i];
            }

        pn=(float)rand()/RAND_MAX;
#ifdef DBG
        printf("cust#%i:randthrow:%4.4f into: ", ncusts, pn); 
        for(i=0;i<ac->asz;++i) 
            if(ac->msk[i])
                printf("%4.4f ", ac->af[i]); 
#endif
        for(i=0;i<ac->asz;++i) {
            if(!ac->msk[i])
                continue;
            if(pn<ac->af[i]) {
                choseni=i;
                break;
            }
        }

        if(choseni != 0) {
            ac->a[choseni]++; // no masking required
            if(ac->a[choseni] == ac->mx[choseni])
                ac->msk[choseni] = 0;
#ifdef DBG
            printf("--> custs+1 existing table %i, now has %i custs\n", choseni, ac->a[choseni]); 
#endif
        } else {
            ac->asz++;
            CONDREALLOC4(ac->asz, ac->gbuf, GBUF, ac->a, ac->af, ac->msk, ac->mx, int, float, unsigned char, int);
            for(i=ac->gbuf-GBUF;i<ac->gbuf;++i) 
                ac->mx[i] = (int)(0.5+normrand(6, 1));
            ac->a[ac->asz-1]=1;
#ifdef DBG
            printf("- NEW TABLE %i! its first customer is #%i\n", ac->asz-1, ncusts); 
#endif
        }
        ncusts++;
#ifdef DBG
        printf("ac->msk: "); 
        for(i=1;i<ac->asz;++i)
            printf("%i ", (int)ac->msk[i]); 
        printf("\n"); 
        printf("ac->mx:  "); 
        for(i=1;i<ac->asz;++i)
            printf("%i ", ac->mx[i]); 
        printf("\n"); 
#endif
    } while(ncusts<TOTCUSTS);

    // final state needs someextra work:
    tsum=1;
    for(i=1;i<ac->asz;++i) 
        if(ac->msk[i])
            tsum += ac->a[i];
    ac->af[0]=1.0/tsum;
    tf=ac->af[0];
    for(i=1;i<ac->asz;++i) {
        if(ac->msk[i]) {
            ac->af[i]=tf+(float)ac->a[i]/tsum;
            tf=ac->af[i];
        }
    }

    // print out final state
    printf("Final state: numtables:%i\nOPEN: ", ac->asz); 
    for(i=0;i<ac->asz;++i)
        if(ac->msk[i])
            printf("T_%i:#custs%i:prob%4.4f ", i, ac->a[i], (i==0)?ac->af[i]:ac->af[i]-ac->af[i-1]); 
    printf("\nCLOSED: "); 
    for(i=1;i<ac->asz;++i)
        if(!ac->msk[i])
            printf("T_%i:#custs%i ", i, ac->a[i]);
    printf("\n"); 

    free(ac->a);
    free(ac->af);
    free(ac->mx);
    free(ac->msk);
    free(ac);
    return;
}

void prtusage(void)
{
    // printf("Generates N recursive for-loops for the range of nucelotides (i.e. range of 4).\n"); 
    // printf("You need to give an integer N as argument.\n");
    printf("No args for now\n"); 
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
    if(argc != 1) {
        prtusage();
        exit(EXIT_FAILURE);
    }
    probme();

    return 0;
}
