#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void prtusage(void)
{
	printf("One arg please: 1) string in FILENAME:COLUMN:SEPARATOR:COMMENTSYES:HEADERYES form\n");
	printf("Separator most probably \" \" or \",\"\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	if(argc != 2)
		prtusage();

	char t[]=":";
	char *tk=strtok(argv[1], t);

	if(tk ==NULL) {
		printf("strtok returned NULL\n"); 
	} else
		printf("First strtok:\n%s(size=%zu)\n", tk, strlen(tk));

	while( (tk=strtok(NULL, t)) != NULL) {
		printf("%s(size=%zu)\n", tk, strlen(tk));
	}

   return 0;
}
