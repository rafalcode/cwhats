#include <math.h>

float gasdev(int *idum)
{
    static int iset=0;
    static float gset;
    float fac,r,v1,v2;
    float ran1();

    if  (iset == 0) {
        do {
            v1=2.0*((float)rand()/(RAND_MAX+1))-1.0;
            v2=2.0*((float)rand()/(RAND_MAX+1))-1.0;
            r=v1*v1+v2*v2;
        } while (r >= 1.0 || r == 0.0);
        fac=sqrt(-2.0*log(r)/r);
        gset=v1*fac;
        iset=1;
        return v2*fac;
    } else {
        iset=0;
        return gset;
    }
}
