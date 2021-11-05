/*
ome numbers have funny properties. For example:

    89 --> 8¹ + 9² = 89 * 1

    695 --> 6² + 9³ + 5⁴= 1390 = 695 * 2

    46288 --> 4³ + 6⁴+ 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51

Given a positive integer n written as abcd... (a, b, c, d... being digits) and a positive integer p

    we want to find a positive integer k, if it exists, such as the sum of the digits of n taken to the successive powers of p is equal to k * n.

In other words:

    Is there an integer k such as : (a ^ p + b ^ (p+1) + c ^(p+2) + d ^ (p+3) + ...) = n * k

If it is the case we will return k, if not return -1.

Note: n and p will always be given as strictly positive integers.

dig_pow(89, 1) should return 1 since 8¹ + 9² = 89 = 89 * 1
dig_pow(92, 1) should return -1 since there is no k such as 9¹ + 2² equals 92 * k
dig_pow(695, 2) should return 2 since 6² + 9³ + 5⁴= 1390 = 695 * 2
dig_pow(46288, 3) should return 51 since 4³ + 6⁴+ 2⁵ + 8⁶ + 8⁷ = 2360688 = 46288 * 51
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int comp(const int *a, const int *b, int n)
{
    if(!n)
        return 0;
    int i, j, sq;
    unsigned char mi;
    unsigned char *c=calloc(n, sizeof (unsigned char));

    for(i=0;i<n;++i) {
        mi=0;
        sq=a[i]*a[i];
        for(j=0;j<n;++j) {
            if(c[j])
                continue;
            if(sq==b[j]) {
                c[j]=1;
                mi=1;
                break;
            }
        }
        if(!mi) {
            printf("i:%i,%i,%i\n", i, a[i], a[i]*a[i]); 
            return 0;
        }
    }

    int sum=0;
    for(i=0;i<n;++i) {
        // printf("%i\n", c[i]); 
        sum+=c[i];
    }
    // printf("\n"); 
    if(sum!=n)
        return 0;

    free(c);
    return 1;
}

int main(int argc, char *argv[])
{
    int a[9]={121, 144, 19, 161, 19, 144, 19, 11, 1008};
    int b[9]={14641, 20736, 361, 25921, 361, 20736, 361, 121, 12340};
    // int a[8] = {121, 144, 19, 161, 19, 144, 19, 11};
    // int b[8] = {121, 14641, 20736, 361, 25921, 361, 20736, 361};
    printf("%s\n", (comp(a, b, 9))?"same":"wrong");
   return 0;
}
