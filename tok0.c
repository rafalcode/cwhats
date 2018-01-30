#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

	char s[]="ID=id39;Parent=rna4;Dbxref=GeneID:106566220,Genbank:XM_014138059.1;gbkey=mRNA;gene=LOC106566220;product=forkhead box protein I1c-like;transcript_id=XM_014138059.1";

	printf("String to look at:\n%s\n", s);
	char *tk=strtok(s, ":,");

	if(tk ==NULL) {
		printf("strtok returned NULL\n"); 
	} else
		printf("First strtok:\n%s(size=%zu)\n", tk, strlen(tk));

	while( (tk=strtok(NULL, ":,")) != NULL) {
		printf("%s(size=%zu)\n", tk, strlen(tk));
	}

   return 0;
}
