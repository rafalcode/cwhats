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
	if(argc != 2) {
        printf("Test an introduced directory name, by touching a file inside it.\n"); 
		exit(EXIT_FAILURE);
	}
    size_t dnlen=strlen(argv[1]);
    size_t rflen=strlen(FNAME);

    DIR *d;
    if((d = opendir(argv[1])) == NULL) {
        printf("directory %s doesn't exist. Bailing out.\n", argv[1]); 
        exit(EXIT_FAILURE);
    }
    closedir(d);
    char *buf=calloc(dnlen+rflen+1+1, sizeof(char)); /* +1 for slash, +1 for zero term */
    sprintf(buf, "%s/%s", argv[1], FNAME);
    printf("Attempting now to touch %s.\n", buf); 

    FILE *fp=fopen(buf, "w");
    fclose(fp);
    free(buf);

    return 0;
}
