/* doub0:
 * we're inrertested in an vector of doubles
 * and how close each member is to a certain integer.
 * In fact, there are three of these integers of interest:0, 1, and 2.
 * So we call 3 the dimension in this progam.
 * More precisely, the category dimension.
 *
 * However the actuall number of categories is the catquan, the category quantity.
 *
 * Important We are not interested in which of the three inegers a double is closest to.
 * We just want to know how close and categorise the double based on this closeness.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define CATQUAN 6 // quantities of categories

typedef unsigned char boole;
typedef enum
{
    VG, /* 0, Very Good */
    G, /*1, Good */
    R, /*2, Reasonable */
    M, /* 3, Mediocre */
    P,  /*4, Poor */
    VP, /*5, Very Poor */
    E, /* 6 Excellent, conveniently  can also mean Exact, or Exact Enough. iYES YES, I know it doesn't follow from sequence */
} cat_t;

typedef struct  /* dc_t, a double and category type */
{
    double d;
    cat_t c;
} dc_t; 

int *catdoub(double *pv, int pvsz, int totcats)
{
    int i, j;
    boole catted; // was this categorized?
    // even with -std=c99 you can't do this:
    // double thres[totcats]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
    //              1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
    //              1.2, 1.1,1.05,1.01,1.001, 1.0001};
    double thres[]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
                 1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
                 1.2, 1.1,1.05,1.01,1.001, 1.0001};
    int *cats=calloc(totcats+1, sizeof(int));
    for(i=0;i<pvsz;++i) {
        catted=0;
        for(j=0;j<totcats;++j) {
            if(pv[i]>=thres[j]) {
                cats[j]++;
                catted=1;
                break;
            }
        }
        if(!catted)
            cats[totcats]++; // i.e. below 0.0001
    }
    return cats;
}

void catdoub2(dc_t *dc, int dcsz, int catdim, int catquan)
{
    int i, j;
    boole badfloatseen=0; // there's a possible of a weird float, and we want to catch it
    boole jj, cat2 /* the real catquan, 0: c very close, VG; 5= far, VP */, catted; // was this categorized?
    // even with -std=c99 you can't do this:
    // double thres[totcats]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
    //              1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
    //              1.2, 1.1,1.05,1.01,1.001, 1.0001};
    double divs[]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
                 1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
                 1.2, 1.1,1.05,1.01,1.001, 1.0001};
    int totdivs=catdim*catquan;
    for(i=0;i<dcsz;++i) {
        if((dc[i].d>=2.5) | (dc[i].d<.0)) {
            if(!badfloatseen) {
                printf("Warning: at least 1 bad float value was seen. You really need to check that dataset, as current analysis will be flawed!\n");  
                badfloatseen=1;
                // will only be printed once, though all bad floats will be skipped.
            }
            continue;
        }
        catted=0;
        for(j=0;j<totdivs;++j) {
            if(dc[i].d>=divs[j]) {
                jj=(boole)(j/catquan)%2;
                if(jj)
                    cat2=(boole)(j%catquan);
                else 
                    cat2=(boole)(catquan-1-(j%catquan));
                dc[i].c = cat2;
                catted=1;
                break;
            }
        }
        if(!catted)
            dc[i].c = 0; // the fall through ... very close to zero
    }
    return;
}

void catdoub3(dc_t *dc, int dcsz, double *divs, int totdivs)
{
    /* holy sh*t, I really should be using floor() */
    int i, j;
    boole badfloatseen=0; // there's a possible of a weird float, and we want to catch it
    boole jj, catted;
    // even with -std=c99 you can't do this:
    // double thres[totcats]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
    //              1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
    //              1.2, 1.1,1.05,1.01,1.001, 1.0001};
    // double divs[]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
    //              1.9999, 1.999, 1.99, 1.95, 1.9, 1.8, 
    //              1.2, 1.1,1.05,1.01,1.001, 1.0001};
    double fd; // floored double;
    double closeness;
    double *ff=malloc(dcsz*sizeof(double));
    for(i=0;i<dcsz;++i) {
        if((dc[i].d>=2.5) | (dc[i].d<.0)) {
            if(!badfloatseen) {
                printf("Warning: at least 1 bad float value was seen. You really need to check that dataset, as current analysis will be flawed!\n");  
                badfloatseen=1;
                // will only be printed once, though all bad floats will be skipped.
            }
            continue;
        }
        fd=dc[i].d - floor(dc[i].d);
        if(fd<0.5)
            closeness=fd;
        else
            closeness=1.-fd;
        ff[i]=closeness;
        catted=0;
        for(j=0;j<totdivs;++j) {
            if(closeness>=divs[j]) {
                dc[i].c = totdivs-1-j;
                catted=1;
                break;
            }
        }
        if(!catted)
            dc[i].c = E; // the fall through ... very close to zero: Excellent of Exact.
    }
    for(i=0;i<dcsz;++i) 
        printf("%4.6f ", ff[i]); 
    printf("\n"); 
    free(ff);
    return;
}

void arrcats(int *cats, int catdim, int catquan) // arrange categories
{
    int i, j;
    boole oddi;
    printf("%10s %10s %10s %10s %10s %10s\n", "VG:<0.01", "G<0.02", "R:<0.05", "M:<0.1", "P:<0.2", "VP:>=0.2"); 
    for(i=0;i<catdim;++i) {
        oddi=i%2;
        if(oddi) {
            for(j=i*catquan;j<(i+1)*catquan;++j)
                printf("%10i ", cats[j]); 
        } else {
            for(j=(i+1)*catquan-1;j>=i*catquan;--j)
                printf("%10i ", cats[j]); 
        }
        printf("\n"); 
    }
    printf("%10i\n", cats[catdim*catquan]); 
    return;
}

int *arrcats2(int *cats, int catdim, int catquan) // arrange categories
{
    int i, j, jj;
    boole oddi;
    int *cats2=calloc(catquan, sizeof(int));
    for(i=0;i<catdim;++i) {
        oddi=i%2;
        if(oddi) {
            printf("Od: "); 
            for(j=i*CATQUAN;j<(i+1)*CATQUAN;++j) {
                jj=j%CATQUAN;
                printf("%i ", jj); 
                cats2[jj]+= cats[j];
            }
            printf("\n"); 
        } else {
            printf("Ev: "); 
            for(j=(i+1)*CATQUAN-1;j>=i*CATQUAN;--j) {
                jj=CATQUAN-1-(j%CATQUAN);
                printf("%i ", jj); 
                cats2[jj]+= cats[j];
            }
            printf("\n"); 
        }
    }
    return cats2;
}

int main(int argc, char *argv[])
{
    int i, j;
    int totsnps=16;
    double pv[16]={1.00071, 1.019, 1.00349, 1.99589, 1.82726, 1.93655, 2, 2, 1.02263, 1.96013, 1.02247, 1.02236, 2, 1.00229, 1.00252, 1.00247};
    double pv2[16]={0};
    for(i=0;i<totsnps;++i) 
        pv2[i] = pv[i]-floor(pv[i]);
    for(i=0;i<totsnps;++i) 
        printf("%4.6f ", pv2[i]); 
    printf("\n"); 

    int catdim=3;
    int catquan=CATQUAN;
    int *cats=catdoub(pv, totsnps, catdim*catquan); // but cats is actually one bigger.
    arrcats(cats, catdim, catquan);
    printf("\n"); 
    int *cats2=arrcats2(cats, 3, catquan);
    // arrcats(cats, 3, catquan);
    printf("%10s %10s %10s %10s %10s %10s\n", "VG:<0.001", "G<0.01", "R:<0.05", "M:<0.1", "P:<0.2", "VP:>=0.2"); 
    for(i=0;i<catquan;++i)
        printf("%10i ", cats2[i]); 
    printf("\n"); 
    printf("Legend: V=Very; G=Good; R=Reasonable; M=Mediocre; P=Poor, E=Excellent/Exact\n"); 
    free(cats);
    free(cats2);
    printf("\n"); 
    printf(">>> Approach with struct dc_t:\n");
    dc_t *dc=malloc(totsnps*sizeof(dc_t));
    for(i=0;i<totsnps;++i)
        dc[i].d=pv[i];

    catdoub2(dc, totsnps, catdim, catquan);
    for(i=0;i<totsnps;++i) 
        printf("%4.6f|%i ", dc[i].d, dc[i].c);
    printf("\n"); 
    printf(">>> Approach with struct dc_tand floor(), i.e. catdoub3():\n");
    int divsz=6;
    double divs[]={.2, .1, .05, .02, .01, .001};
    catdoub3(dc, totsnps, divs, divsz);
    for(i=0;i<totsnps;++i) 
        printf("%4.6f|%i ", dc[i].d, dc[i].c);
    printf("\n"); 

    free(dc);
    return 0;
}
