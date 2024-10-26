// chatgpt 
// // I mean it doesn't work
#include <stdio.h>

int reverse_triple(int i)
{
    // Lookup table for modulo 3 without using %
    static const int mod3[] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
    
    // Multiplying by 0xAAAAAAAB and shifting can simulate division by 3
    // // but hti sis so bizarre, there's only 3 2 bits in an integer, very hard to understand!
    int div3 = (i * 0xAAAAAAAB) >> 33;
    
    // Calculate the reversed position within the triplet
    return (div3 * 3) + (2 - mod3[i]); // also hard to understand
}

int main()
{
    for (int i = 0; i < 12; ++i) {
        printf("%d ", reverse_triple(i));
    }
    return 0;
}
