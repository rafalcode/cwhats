/* system calls from c and capturing output */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{

    FILE *fp;

    // char *sysCmd = "uname -a";
    char *sysCmd = "lspci";
    if( (fp = popen(sysCmd, "r")) == NULL) {
        printf("Failed to run command\n" );
        exit(EXIT_FAILURE);
    }

    /* so what we get here is a FILE ppoint, right? WHat;s that? It's a file descriptor
       and to pull text out of it we use fets which relies on a text buffer? */
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    while ((nread = getline(&line, &len, fp)) != -1) {
        // printf("Retrieved line of length %zu:\n", nread);
        fwrite(line, nread, 1, stdout);
    }

    free(line);
    pclose(fp);

    return 0;
}
