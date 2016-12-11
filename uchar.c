/* let's have a look at char and uchar */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

    /* declarations */
    char a=254;
    unsigned char b=(unsigned char)a;
    char i;
    unsigned char j;
    int k;
    for(k=0;k<300;++k) {
        i=k;
        printf("%d:%x ", i, i);
    }
    printf("\n"); 
    for(k=0;k<300;++k) {
        j=k;
        printf("%d:%x ", j, j);
    }
    printf("\n"); 

    printf("%d %d\n", a, b);
    char i2;
    short x=-31998;
    i=x&0xff;
    i2=(x>>8)&0xff;
    printf("%x) %d:%d - %x:%x\n", x, i, i2, i, i2);

    /* Experiment run here: int combine, may result in problems. using short helps, even though it might be a wee less portable */
    short combine;
    combine=i&0x00ff;
    combine |= (i2&0x00ff)<<8;
    printf("%d:%x\n", combine, combine); 

    /* A thing to note in all of this, when using printf and the int format, whenever it detects a neagitve number all later
        bits are set to zero if the container is bigger */
    return 0;
}
