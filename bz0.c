#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bzlib.h>

int main()
{
    const char *ver = BZ2_bzlibVersion();
    // char *ver = BZ2_bzlibVersion();
    printf("%s\n", ver); 
    // printf("%s\n", BZ_VERSION); 
    return 0;
}
