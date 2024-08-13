/* takes 6 digits and assumes it's a time, and will output seconds
 * so we can treat decimally and forgetr abou t60 sec sand imdm3: IMage Detailer Manual (Needs conft focus point file - 3 subimages, Top left. top right, bottom strip)
 * Takes from imdac3.c */
#include<math.h>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<sys/stat.h>

#define THROWAWAYMEMSZ 128

int main (int argc, char *argv[])
{
    
    if(argc!=2) {
        printf("give a filename\n");
        exit(EXIT_FAILURE);
    }


	struct stat ifsta;
	if(stat(argv[1], &ifsta) == -1) {
		fprintf(stderr,"Can't stat the input file %s", argv[1]);
		exit(EXIT_FAILURE);
	}
    struct tm *mtime = localtime(&ifsta.st_mtime);
    if (mtime == NULL) {
        perror("localtime");
        exit(EXIT_FAILURE);
    }

    // Create a buffer to hold the formatted time string
    char *mtime_str=calloc(THROWAWAYMEMSZ, sizeof(char));
    if (strftime(mtime_str, THROWAWAYMEMSZ, "%H:%M:%S", mtime) == 0) {
        fprintf(stderr, "strftime returned 0");
        exit(EXIT_FAILURE);
    }

    printf("%s\n", mtime_str);
    free(mtime_str);

    return 0;
}
