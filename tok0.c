#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char s[]="ID=rna3;Parent=gene3;Dbxref=GeneID:106560213,Genbank:XM_014126719.1;Name=XM_014126719.1;gbkey=mRNA;           gene=LOC106560213;partial=true;product=phospholipase B1%2C membrane-associated-like;start_range=.,3827;transcript_id=XM_014126719.1";
	printf("String to look at:\n%s\n", s);
	char t[]=":,=;";

    /* note: I know it's slightly verbose, but it's easier if you you take the first one separately */
	char *tk=strtok(s, t);
    printf("\n"); 
	if(tk ==NULL) {
		printf("strtok returned NULL\n"); 
	} else
		printf("First strtok: \"%s\" (size=%zu)\n", tk, strlen(tk));

	while( (tk=strtok(NULL, t)) != NULL) {
		printf("\"%s\" (size=%zu)\n", tk, strlen(tk));
	}

   return 0;
}
