/* this prog demonstrates how when using sscanf to pick out intergets hidden in strings
 * that you need to use %d and not %i.
 */
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>

int main(int argc, char *argv[])
{
    char *anystr[2]={"C08_P00430", "C03_P00331"};
    int i, i1, i2, sca;
    for(i=0;i<2;++i) {
        sca=sscanf(anystr[i], "C%d_P%d", &i1, &i2); // do not use %i!
        printf("Source string = \"%s\"\n", anystr[i]); 
        printf("Return val=%i\n", sca); 
        printf("i1 is %i and i2 is %i. Added = %i\n", i1, i2, i1+i2);
    }

    return 0;
}
