/* from https://phoxis.org/2013/05/04/generating-random-numbers-from-normal-distribution-in-c/ */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

float normrand(float mu, float sigma)
{
    float U1, U2, W, mult;
    static float X1, X2;
    static int call = 0;

    if (call == 1) {
        call = !call;
        printf("Using previously created normrnds %4.4f for this call.\n", X2); 
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
    printf("Generated two normrnds: %4.4f and %4.4f\n", X1, X2); 

    call = !call;

    return (mu + sigma * (float) X1);
}

int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("Two args required: mean and variance (0, 1 for standard normal\n"); 
        exit(EXIT_FAILURE);
    }
    float f=normrand(atof(argv[1]), atof(argv[2]));
    printf("First normrand is %4.4f\n", f);
    f=normrand(atof(argv[1]), atof(argv[2]));
    printf("Second normrand is %4.4f\n", f);
    f=normrand(atof(argv[1]), atof(argv[2]));
    printf("Third normrand is %4.4f\n", f);

    return 0;
}

