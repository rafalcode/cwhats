/* Fisher Yates and making it look like
 * which I call fy0.c
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SEED 42

enum
{
    // Assumes W = 32 (omitting this)
    N = 624,
    M = 397,
    R = 31,
    A = 0x9908B0DF,

    F = 1812433253,

    U = 11,
    // Assumes D = 0xFFFFFFFF (omitting this)

    S = 7,
    B = 0x9D2C5680,

    T = 15,
    C = 0xEFC60000,

    L = 18,

    MASK_LOWER = (1ull << R) - 1,
    MASK_UPPER = (1ull << R)
};

static uint32_t  mt[N];
static uint16_t  index;

// Re-init with a given seed
void Initialize(const uint32_t  seed)
{
    uint32_t  i;
    mt[0] = seed;
    for ( i = 1; i < N; i++ )
        mt[i] = (F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
    index = N;
}

static void Twist()
{
    uint32_t  i, x, xA;

    for ( i = 0; i < N; i++ ) {
        x = (mt[i] & MASK_UPPER) + (mt[(i + 1) % N] & MASK_LOWER);

        xA = x >> 1;

        if ( x & 0x1 )
            xA ^= A;

        mt[i] = mt[(i + M) % N] ^ xA;
    }
    index = 0;
}

// Obtain a 32-bit random number
void ExtractU32a(unsigned *arr, unsigned *tarr, int sz)
{
    // extract uint's from Array
    uint32_t  y;
    int i, j;
   
    for(j=0;j<sz;++j) {
        i = index;
        if ( index >= N ) {
            Twist();
            i = index;
        }
        y = mt[i];
        index = i + 1;

        y ^= (y >> U);
        y ^= (y << S) & B;
        y ^= (y << T) & C;
        y ^= (y >> L);

        tarr[j] = arr[y%sz];
    }
    memcpy(arr, tarr, sz*sizeof(unsigned));
}

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. One arg required: N an integer.\n");
		exit(EXIT_FAILURE);
	}
    Initialize(SEED);
    int i, n;
    n=atoi(argv[1]);
    unsigned char allsame=0;

    unsigned *arr=malloc(n*sizeof(unsigned));
    for(i=0;i<n;++i)
        arr[i]=i+1;
    unsigned *tarr=malloc(n*sizeof(unsigned)); // temp array

    int k=0;
    while(!allsame) {
        if(k==0)
            printf("Start with: ");
        else
            printf("Round %02i: ", k); 

        for(i=0;i<n;++i) {
            printf("%u", arr[i]);
            putchar((i==n-1)?'\n':' '); 
        }
        ExtractU32a(arr, tarr, n);

        allsame=1;
        for(i=1;i<n;++i)
            if(arr[i]!=arr[0]) {
                allsame=0;
                break;
            }
        k++;
    }

    printf("Round %02i: ", k); 
    for(i=0;i<n;++i) {
        printf("%u", arr[i]);
        putchar((i==n-1)?'\n':' '); 
    }

    free(arr);
    free(tarr);
    return 0;
}
