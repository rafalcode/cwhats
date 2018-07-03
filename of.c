/* give out file names base don input */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *of=fopen("ofname.txt", "w");
    fprintf(of, "cap G on end of this this strinG");
    fseek(of, -1, SEEK_CUR);
    fprintf(of, "g\n");
    fclose(of);
    system("cat ofname.txt");

   return 0;
}
