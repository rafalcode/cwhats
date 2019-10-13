/* system calls from c and capturing output */
#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )
{

  FILE *fp;
  char path[20] = {0};

  // char *sysCmd = "uname -a";
  char *sysCmd = "lspci";
  if( (fp = popen(sysCmd, "r")) == NULL) {
    printf("Failed to run command\n" );
    exit(EXIT_FAILURE);
  }

  /* so what we get here is a FILE ppoint, right? WHat;s that? It's a file descriptor
      and to pull text out of it we use fets which relies on a text buffer? */

  while (fgets(path, sizeof(path)-1, fp) != NULL) {
    printf("%s", path);
    printf("\n"); 
  }

  /* close */
  pclose(fp);

  return 0;
}
