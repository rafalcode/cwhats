/* playing with c's time function */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define __USE_XOPEN // because strptime not recognised otherwise
#include <time.h>

#define STRSZ 128

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Usage: prints changed version of input string.\n");
        exit(EXIT_FAILURE);
    }

    int i;
    unsigned sl = strlen(argv[1]);
    printf("%s\n", argv[1]); 
    printf("Conv:\n"); 
    printf("%i", 79); // 20: aka 9-2, 9-0
    for(i=sl-1;i>=sl-6;--i) {
        if(argv[1][i] == 'e')
            putchar('_');
        else if(i/2)
            putchar(argv[1][i]-32);
        else
            putchar(argv[1][i]+1);
    }
    printf("%i", 91); // 20: aka 9-1, 9-8
    putchar('\n');

    return 0;
}
