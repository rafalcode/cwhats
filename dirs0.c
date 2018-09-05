/* dirs0.c, an exercise in checking whether a directory exists and then writing a file in that directory.
 * Note that if diretroy does not exist, it is not created.
 * The idea is that a DIR* needs to be declared and an attempt must be made to open it.
 * then the filename must be "catted", though not before a "/" is catted before hand
 * and them a FILE* is declared but the DIR* is surrendered before this as the file writing
 * does not require a directory, it works on the string and the exitence of the necessary /'s */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h> 

#define DNAME "anytmpdir"
#define FNAME "randomfn"

int main(int argc, char *argv[])
{
    char *myt=calloc(32, sizeof(char));
    strcpy(myt, DNAME);

    DIR *d;
    if((d = opendir(myt)) == NULL) {
        printf("directory %s doesn't exist.\n", DNAME); 
        free(myt);
        exit(EXIT_FAILURE);
    }
    closedir(d);
    strcat(myt, "/");
    strcat(myt, FNAME);

    FILE *fp=fopen(myt, "w");
    fclose(fp);

    free(myt);

    return 0;
}
