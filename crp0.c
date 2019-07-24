#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 5
#define CONDREALLOC(x, b, c, a1, a2, t1, t2); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a1)=realloc((a1), (b)*sizeof(t1)); \
        (a2)=realloc((a2), (b)*sizeof(t2)); \
    }

void probme(int *a, int asz)
{
    int gbuf=GBUF;
    int a=calloc(gbuf, sizeof(int))
    int as
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
    if(choseni != )
        a[choseni]++;
    else {
        CONDREALLOC

    for(i=0;i<asz;++i) 
        printf("%4.4f ", af[i]);
    printf("pn=%4.4f choseni=%i\n", pn, choseni); 
    free(af);
    return;
}

void probme2(void)
{
    int gbuf=GBUF;
    int a=calloc(gbuf, sizeof(int))
    int asz=1;
    int tsum=1;
    float af=malloc(gbuf*sizeof(float));
    int choseni;
    float pn;

    while(asz<5) {

        for(i=1;i<asz;++i) 
            tsum += a[i];
        af[0]=1.0/tsum; // notinal prob of this empty table (the waiting next)
        for(i=1;i<asz;++i) 
            af[i]=af[i-1]+(float)a[i]/tsum;
        pn=(float)rand()/RAND_MAX;
        for(i=0;i<asz;++i)
            if(pn<af[i]) {
                choseni=i;
                break;
            }
        if(choseni != )
            a[choseni]++;
        else {
            asz++;
            CONDREALLOC(asz, gbuf, GBUF, a, af, int, float);
            a[asz-1]=1;

                for(i=0;i<asz;++i) 
                    printf("%4.4f ", af[i]);
            printf("pn=%4.4f choseni=%i\n", pn, choseni); 
        }
        free(af);
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
        int a[SYMBASZ]= {0,4,1,2};
        probme(a, SYMBASZ);
        int b[2]= {0,2};
        probme(b, 2);

        return 0;
    }