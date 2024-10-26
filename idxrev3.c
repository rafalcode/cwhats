/* idxrev.c, reversing every second triple of indices, useful for L->M->R->M->L traversings (M for middle). */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
	if(argc!=2) {
		printf("Error. Pls supply 1 arg, integer n, size of array.\n");
		exit(EXIT_FAILURE);
	}
    int i, n=atoi(argv[1]);

    // first creat an array which we're interesting in LRL traversing.
    char c[n];
    for(i=0;i<n;++i)
        c[i]=(char)(i+65);

    // print out to have a look:
    printf("Normal traversal:\n"); 
    for(i=0;i<n;++i) {
        putchar(c[i]);
        putchar((i!=(n-1))?' ':'\n');
    }

    int ai[n] /* alternate index */;
    static const int mod3[] = {0, 1, 2, 0, 1, 2, 0, 1, 2}; 
    int div3;
    for(i=0;i<n;++i) {
        // Multiplying by 0xAAAAAAAB and shifting can simulate division by 3
        div3 = (i * 0xAAAAAAAB) >> 33;
    
        // Calculate the reversed position within the triplet
        ai[i] = (div3 * 3) + (2 - mod3[i]);
    }


    printf("Traversal reversing every second pair:\n"); 
    for(i=0;i<n;++i) {
        putchar(c[ai[i]]);
        putchar((i!=(n-1))?' ':'\n');
    }

   return 0;
}

/*
How It Works:
^ is XOR the exclusive OR
i.e. not normal OR, which |
i = 0 → 0 ^ ((0 >> 1) & 1) = 0 ^ 0 = 0
i = 1 → 1 ^ ((1 >> 1) & 1) = 1 ^ 0 = 1
i = 2 → 2 ^ ((2 >> 1) & 1) = 2 ^ 1 = 3 // 2 is even, so it's an add op?
i = 3 → 3 ^ ((3 >> 1) & 1) = 3 ^ 1 = 2 // 3 is odd, so it's a sub op?
i = 4 → 4 ^ ((4 >> 1) & 1) = 4 ^ 0 = 4
i = 5 → 5 ^ ((5 >> 1) & 1) = 5 ^ 0 = 5
i = 6 → 6 ^ ((6 >> 1) & 1) = 6 ^ 1 = 7
i = 7 → 7 ^ ((7 >> 1) & 1) = 7 ^ 1 = 6
This will give you the pattern 0, 1, 3, 2, 4, 5, 8, 7 without using if statements.

Also:
((i >> 1) & 0x1) checks for every second pair.

*/
