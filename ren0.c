#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    if(argc!=2) {
        printf("Error. Pls one filename\n");
        exit(EXIT_FAILURE);
    }
    int i;

    size_t ln;
    ln=strlen(argv[1]);
    for(i=0;i<ln;++i) {
        printf("%c:%x ", argv[1][i], argv[1][i]);
    }
    return 0;
}
