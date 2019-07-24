/* this prog demonstrates how when using sscanf to pick out intergets hidden in strings
 * that you need to use %d and not %i.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

int main(int argc, char *argv[])
{
    char *anystr="C08_P00430";
    int i1, i2;
    // sscanf(anystr, "C%i_P%i", &i1, &i2); // fails pretty bad ebcaue of leading zeros
    sscanf(anystr, "C%d_P%d", &i1, &i2);
    printf("i1 is %i and i2 is %i\n", i1, i2);

    return 0;
}
