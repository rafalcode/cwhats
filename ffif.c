/* system calls from c and capturing output */
#include <stdio.h>
#include <stdlib.h>

void prtusage(void)
{
    printf("ffif: stores ffmpeg -i into on a file and gets it into a buffer\n");
    printf("1 arg requires ... the media file\n"); 
    exit(EXIT_FAILURE);
}

int main( int argc, char *argv[] )
{
    if(argc != 2) {
        prtusage();
        exit(EXIT_FAILURE);
    }

  FILE *fp=NULL;
  char path[4096] = {0};
  char cmdbuf[4096] = {0};

  // char *sysCmd = "uname -a";
  strcat(cmdbuf, "ffmpeg -i ");
  strcat(cmdbuf, argv[1]);
  return 0;


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
