#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// FILE *ofp=(FILE *)stdout;
#define ofp stdout

int main(int argc, char *argv[])
{

   /* print stuff out */
   fprintf(ofp, "Res_1: %s\n", "somedata");

   return 0;
}
