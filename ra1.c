/* from: https://www.geeksforgeeks.org/little-and-big-endian-mystery/
 * and it mostly ecertainly is an mystery */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function to show bytes in memory, from location start to start+n*/
void show_mem_rep(char *start, int n)
{
    int i;
    for (i = 0; i < n; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

/*Main function to call above function for 0x01234567*/
int main()
{
    int i = 0x01234567;
    printf("Show 0x%x rendered in bytes to see endianness:\n", i);
    show_mem_rep((char *)&i, sizeof(i));
    // getchar();
    return 0;
}
