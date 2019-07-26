#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 2
#define MAXTAB 5
#define MAXCPT 10 // max customers per table
#define TOTCUSTS 132 // total customers to process
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

typedef struct
{
    int vbf, vsz, *v;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->v=malloc(avc->vbf*sizeof(int));
    avc->vsz=0;
    return avc;
}

void condrea_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, int);
    return;
}

void norm_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    avc->v=realloc(avc->v, avc->vsz*sizeof(int));
    return;
}

void free_avc(av_c *avc)
{
    free(avc->v);
    free(avc);
    return;
}

void probme(int *a, int asz)
{
    int i;
    int tsum=1;
    float *af=malloc((asz-1)*sizeof(float));
    for(i=1;i<asz;++i) 
        tsum += a[i];
    af[0]=1.0/tsum; // notinal prob of this empty table (the waiting next)
    for(i=1;i<asz;++i) 
        af[i]=af[i-1]+(float)a[i]/tsum;
    float pn=(float)rand()/RAND_MAX;
    int choseni;
    for(i=0;i<asz;++i)
        if(pn<af[i]) {
            choseni=i;
            break;
        }
    if(choseni != 0)
        a[choseni]++;

    for(i=0;i<asz;++i) 
        printf("%4.4f ", af[i]);
    printf("pn=%4.4f choseni=%i\n", pn, choseni); 
    free(af);
    return;
}

void probme2(void)
{
    int i, gbuf=GBUF;
    int *a=calloc(gbuf, sizeof(int));
    int asz=1;
    int tsum;
    float *af=malloc(gbuf*sizeof(float));
    int choseni;
    float pn;
    unsigned char found;
    int ncusts=0;

    do {
        tsum=1;
        for(i=1;i<asz;++i) 
            tsum += a[i];
        af[0]=1.0/tsum; // notional prob of this empty table (the waiting next)
        for(i=1;i<asz;++i) 
            af[i]=af[i-1]+(float)a[i]/tsum;
        pn=(float)rand()/RAND_MAX;
#ifdef DBG
        printf("cust#%i:randthrow:%4.4f into: ", ncusts, pn); 
        for(i=0;i<asz;++i) 
            printf("%4.4f ", af[i]); 
#endif
        found=0;
        for(i=0;i<asz-1;++i)
            if(pn<af[i]) {
                choseni=i;
                found=1;
                break;
            }
        if(!found)
            choseni=asz-1;

        if(choseni != 0) {
            a[choseni]++;
#ifdef DBG
            printf("--> custs+1 existing table %i, now has %i custs\n", choseni, a[choseni]); 
#endif
        } else {
            asz++;
            CONDREALLOC2(asz, gbuf, GBUF, a, af, int, float);
            a[asz-1]=1;
#ifdef DBG
            printf("- 1cust for new table %i\n", asz-1); 
#endif
        }
        ncusts++;
    } while(asz<MAXTAB);

    // final state needs someextra work:
    tsum=1;
    for(i=1;i<asz;++i) 
        tsum += a[i];
    af[0]=1.0/tsum;
    for(i=1;i<asz;++i) 
        af[i]=af[i-1]+(float)a[i]/tsum;

    // print out final state
    printf("Final state: numtables:%i\n", asz); 
    for(i=0;i<asz;++i)
        printf("tab%i:#custs%i:prob%4.4f ", i, a[i], (i==0)?af[i]:af[i]-af[i-1]); 
    printf("\n"); 

    free(a);
    free(af);
    return;
}

void probme3(void) /* version with mask */
{
    /* OK, so this won't be that easy. the full table needs to be taken out of the probability
     * line. Best way is a mask, topen, which, if 0, will be ignored */
    int i, gbuf=GBUF;
    int *a=calloc(gbuf, sizeof(int));
    unsigned char *topen=malloc(gbuf*sizeof(unsigned char)); // if 1, table is open for custs
    memset(topen, 1, gbuf*sizeof(unsigned char));
    int asz=1;
    int tsum;
    float *af=malloc(gbuf*sizeof(float));
    float tf;
    int choseni;
    float pn;
    int ncusts=0;

    do {
        tsum=1;
        for(i=1;i<asz;++i)
            if(topen[i])
                tsum += a[i];
        af[0]=1.0/tsum; // notional prob of this empty table (the waiting next)
        tf=af[0];
        for(i=1;i<asz;++i)
            if(topen[i]) {
                af[i]=tf+(float)a[i]/tsum;
                tf=af[i];
            }

        pn=(float)rand()/RAND_MAX;
#ifdef DBG
        printf("cust#%i:randthrow:%4.4f into: ", ncusts, pn); 
        for(i=0;i<asz;++i) 
            if(topen[i])
                printf("%4.4f ", af[i]); 
#endif
        for(i=0;i<asz;++i) {
            if(!topen[i])
                continue;
            if(pn<af[i]) {
                choseni=i;
                break;
            }
        }

        if(choseni != 0) {
            a[choseni]++; // no masking required
            if(a[choseni] == MAXCPT)
                topen[choseni] = 0;
#ifdef DBG
            printf("--> custs+1 existing table %i, now has %i custs\n", choseni, a[choseni]); 
#endif
        } else {
            asz++;
            CONDREALLOC3(asz, gbuf, GBUF, a, af, topen, int, float, unsigned char);
            a[asz-1]=1;
#ifdef DBG
            printf("- NEW TABLE %i! its first customer is #%i\n", asz-1, ncusts); 
#endif
        }
        ncusts++;
#ifdef DBG
        printf("topen: "); 
        for(i=0;i<asz;++i)
            printf("%i ", (int)topen[i]); 
        printf("\n"); 
#endif
    } while(ncusts<TOTCUSTS);

    // final state needs someextra work:
    tsum=1;
    for(i=1;i<asz;++i) 
        if(topen[i])
            tsum += a[i];
    af[0]=1.0/tsum;
    tf=af[0];
    for(i=1;i<asz;++i) {
        if(topen[i]) {
            af[i]=tf+(float)a[i]/tsum;
            tf=af[i];
        }
    }

    // print out final state
    printf("Final state: numtables:%i\nOPEN: ", asz); 
    for(i=0;i<asz;++i)
        if(topen[i])
            printf("T_%i:#custs%i:prob%4.4f ", i, a[i], (i==0)?af[i]:af[i]-af[i-1]); 
    printf("\nCLOSED: "); 
    for(i=0;i<asz;++i)
        if(!topen[i])
            printf("T_%i:#custs%i ", i, a[i]);
    printf("\n"); 

    free(a);
    free(af);
    free(topen);
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
    // int times=atoi(argv[1]);
    // char a[SYMBASZ]={'A', 'C', 'G', 'T'};
    // // char s[times+1]={0};
    // char s[STRSZ]={0};
    // recurseme(a, SYMBASZ, times, s);
    // int a[SYMBASZ]= {0,4,1,2};
    // probme(a, SYMBASZ);
    // int b[2]= {0,2};
    // probme(b, 2);
    probme3();

    return 0;
}
