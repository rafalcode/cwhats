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

int dig_pow(char* ns)
{
    // int i;
    // int mkr;
    // int ln=0;
    // while(1) {
    //     if(!ns[i++])
    //         ln=i;
    //     break;
    // }
    int i, t;
    int n=strlen(ns);
    int *a=calloc(n,sizeof(ns));
    for(i=n-1;i>=0;--i)
        t=1;
        for(j=0;j<i;++j) 
            t=t*a[j];
    for(i=0;i<n;++i)
        printf("%i\n", a[i]);
    return 999;
}

int main(int argc, char *argv[])
{
	if(argc!=2) {
		printf("Error. Pls supply argument (integer).\n");
		exit(EXIT_FAILURE);
	}
    int sz=dig_pow(argv[1]);
    printf("%i\n", sz);
   return 0;
}
