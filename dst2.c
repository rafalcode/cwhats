/* demsontrates using char str[N]'s in data structs.
 * note how N<4 is always given 4 bytes anyway. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct /* simple string and num type */
{
    char st[2];
    int num;
} stn_t;

int main(int argc, char *argv[])
{
    printf("Size of stn is %zu\n", sizeof(stn_t)); 
    stn_t *stn=malloc(2*sizeof(stn_t));
    strncpy(stn[0].st, "op", 3);
    strncpy(stn[1].st, "ok", 3);
    printf("%s and %s\n", stn[0].st, stn[1].st); 
    free(stn);

   return 0;
}
