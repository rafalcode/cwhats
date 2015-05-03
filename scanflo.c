/* scanning floats from a string using sscanf:
 * when scanning from files, the file pointer moves automatically
 * along hte file: not so with strings. Here is a way of reading bytes consumed */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *p="  3.49 4.1111        3.3333    9.919199";
    float f[4];
    int i, nums_now, bytes_now;
    int bytes_consumed = 0, nums_read = 0;

    while ( ( nums_now = sscanf( p + bytes_consumed, "%f%n", f + nums_read, &bytes_now )) > 0 ) {
        bytes_consumed += bytes_now;
        nums_read += nums_now;
    }

    for(i=0;i<4;++i) 
        printf("%f\n", f[i]); 

    return 0;
}
