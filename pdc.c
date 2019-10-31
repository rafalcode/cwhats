/* an exercise in getline: this is the original example from the man pages
 * note that it does lokk quite convenient, because the line's memory need not be allocated
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBUF 4
#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
    }

int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("need two strings as arguments.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    for(i=0;i<strlen(argv[1]);++i) 
        if(argv[1][i] != argv[2][i]) 
            putchar(argv[1][i]);
    putchar('\n');
    exit(EXIT_SUCCESS);
}
