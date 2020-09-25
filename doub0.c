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

#define CATQUAN 6 // quantities of categories

int *catdoub(double *pv, int pvsz, int totcats)
{
    int i, j;
    unsigned char catted; // was this categorized?
    double thres[totcats]={2.2, 2.1,2.05,2.01,2.001, 2.0001,
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
            cats[18]++; // i.e. below 0.0001
    }
    return cats;
}

void arrcats(int *cats, int catdim, int catquan) // arrange categories
{
    int i, j;
    unsigned char oddi;
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
    return;
}

int *arrcats2(int *cats, int catdim, int catquan) // arrange categories
{
    int i, j, jj;
    unsigned char oddi;
    int *cats2=calloc(catquan, sizeof(int));
    for(i=0;i<catdim;++i) {
        oddi=i%2;
        if(oddi) {
            for(j=i*CATQUAN;j<(i+1)*CATQUAN;++j) {
                jj=j%CATQUAN;
                cats2[jj]++;
            }
        } else {
            for(j=(i+1)*CATQUAN-1;j>=i*CATQUAN;--j) {
                jj=CATQUAN-1-(j%CATQUAN);
                cats2[jj]++;
            }
        }
        printf("\n"); 
    }
    return cats2;
}

int main(int argc, char *argv[])
{
    int i, j;
    int totsnps=16;
   double pv[16]={1.00071, 1.019, 1.00349, 1.99589, 1.82726, 1.93655, 2, 2, 1.02263, 1.96013, 1.02247, 1.02236, 2, 1.00229, 1.00252, 1.00247};
   for(i=0;i<totsnps;++i) 
       printf("%4.6f ", pv[i]); 
   printf("\n"); 

   int catdim=3;
   int catquan=CATQUAN;
    int *cats=catdoub(pv, totsnps, catdim*catquan);
    arrcats(cats, catdim, catquan);
    printf("\n"); 
    int *cats2=arrcats2(cats, 3, catquan);
    // arrcats(cats, 3, catquan);
    printf("%10s %10s %10s %10s %10s %10s\n", "VG:<0.001", "G<0.01", "R:<0.05", "M:<0.1", "P:<0.2", "VP:>=0.2"); 
    for(i=0;i<catquan;++i)
        printf("%10i ", cats2[i]); 
    printf("\n"); 
    printf("Legend: V=Very; G=Good; R=Reasonable; M=Mediocre; P=Poor\n"); 
    free(cats);
    free(cats2);
    return 0;
}
