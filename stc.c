/* just checking strncpy to a un-malloced site */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char to[4];
    char *str="nok";
    strncpy(to, str,4);
    printf("%s\n", to); 

   return 0;
}
