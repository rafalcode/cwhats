/* dynamic string exercise */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/md5.h>

int main(int argc, char* argv[])
{
    unsigned char pchar[] = "password";
    unsigned char hash[MD5_DIGEST_LENGTH];    
    printf("%i\n", MD5_DIGEST_LENGTH);
    unsigned char *cp=NULL;
    // printf("Using MD5 function, returns:\n%s\n", MD5(pchar, sizeof(pchar), hash));
    cp = MD5(pchar, sizeof(pchar), hash);
    int cou=0;
    while(cp[cou]) {
        // looks through uninitialiased values (as far as valgrind is concerned) for an \0 */
        printf("%02x", (unsigned char) cp[cou++]);
    }
    printf("\nSize of MD5 strng = %i\n", cou); 

    return 0;
}
