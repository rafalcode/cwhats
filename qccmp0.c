/* quick char comp */
#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
    if(argc!=2) {
        printf("One string arg thanks\n");
        exit(EXIT_FAILURE);
    }

    while(*argv[1])
        putchar(*argv[1]++);
    printf("\n");   

	return 0;
}
