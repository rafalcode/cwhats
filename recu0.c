#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYMBASZ 4 // symbol array size

void recurseme(char *a, int asz, int times, char *s, int j)
{
    int i;
    if(times >= 0) {
        for(i=0;i<asz;++i) {
            s[j]=a[i];
            recurseme(a, asz, times-1, s, j++);
        }
    }  else {
        printf("%s\n", s);
        j=0;
    }
   return;
}

void prtusage(void)
{
    printf("Generates N recursive for-loops for the range of nucelotides (i.e. range of 4).\n"); 
    printf("You need to give an integer N as argument.\n");
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc == 1) {
		prtusage();
		exit(EXIT_FAILURE);
	}
    int times=atoi(argv[1]);
    char a[SYMBASZ]={'A', 'C', 'G', 'T'};
    // char s[times+1]={0};
    char s[256]={0};
    recurseme(a, SYMBASZ, times, s, 0);

   return 0;
}
