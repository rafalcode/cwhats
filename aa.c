/* go around an array:
 * self avoiding, of course,. too trivial otherwise
 * in this way you are able to compare each element of 
 * an array with all the other elements.
 * in circular fashion */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define GBUF 4
#define n 4
#define FLAG unsigned char /* some time also called a boolean */

typedef struct  /* optstruct, a container struct for the options */
{
	FLAG gflg;
} optstruct;


typedef struct
{
	char l; // letter
	int q; //quantity
} oc_t;

void usage(char *pname)
{
	printf("Program \"%s\" demonstrates going around an array in circular order\n", pname);
	printf("while self-avoiding. This allows comparing each member of an array with every other\n");
	printf("Usage: no arguments, produces this help text. Argument \"-g\" means \"go!\", as in carry out procedure.\n");
}

int catchopts(optstruct *opts, int argc, char **argv)
{
	int index, c;
	opterr = 0;

	while ((c = getopt (argc, argv, "g")) != -1)
		switch (c) {
			case 'g':
				opts->gflg = 1;
				break;
			case '?':
				if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
				return 1;
			default:
				usage(argv[0]);
		}

	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	return 0;
}

void occheck(char *aa, oc_t *ocs2, int *gbp, int mxq)
{
	int i, j, ocsz=0;
	int gb=*gbp;
	gb=GBUF;
	unsigned char seenc;
	for(i=0; aa[i]!='\0'; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa[i]== ocs2[j].l) {
				seenc=1;
				ocs2[j].q++;
				if(ocs2[j].q==mxq)
					printf("Max quan found at %i with \n", i, ocs2[j].l); 
				break;
			}
		}
		if(seenc==0) {
			if(ocsz==gb-1) {
				gb+=GBUF;
				ocs2=realloc(ocs2, gb*sizeof(oc_t));
				for(j=gb-GBUF; j<gb; j++)
					ocs2[j].q=0;
			}
			ocs2[ocsz].l=aa[i];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	return;
}


int main(int argc, char *argv[])
{
	if(argc!=1) {
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}
	int oc[26]={0};
	char *aa="ASQLDRFRVFLGWDNGMMLVYQGNKTYEPWLNCDMASPTLSLVSKKAPKILKAADINTTLQPCLAFFIELLLKGIDNERIPNSGSGGREMGLLAPTYSSEATLVTRENNMMEGVHGFENMQDVEVIKLKLPEGYSDVCHFMFMLAGILYIVYDLQMHMSSERETGKFPNPLSDEEFDNPKVVVTNSFVLLEFTVTGAGARPSEQGQEPHNLGATKGSLAISSKTPEIHKDTNPASAQFEGKHTESDAKGVSNEDVFITKERDGREVEPTIKLSKKSVLNPMNVVYNPMLQISEGALRKHSMNDEITILNNTLINKERSVDLGAVSFVNDLLIDKLGCVSGKLAVQLNQSAPPEILHGKDPLTLFLGNTIALMLSKMQRIRVWEEYIFLNLHLALAWEPLLGNLKTHDSQKKWALCGFLIISRIRNLFESEGPVHGLRFSAMPCNTDTRQIKALERFPYAPEKPQWHGDELESPCRLVVASKLLASHDGVSIGKTIGSWPLPAQRYNAYVAWAANDSSILSARPGFAVKEDRLGHSLAQESGTIVVRNPQYGVRFINYNKDEHREFKREATFYPKTVVTHLGAIEGTLMFEIGDAAFTMLHLEEATDAEVRELYYMDMLDKKSSLGRACERIRRVLAPGDHKANGLESAIVSGQNGYEGRIRGLQTFQSNPLKKGRTHMAFCTTLHPFGGLKLVSSQLLKKELAVGTYGHQRTVLHSAEYSCPTSIPNLEGLMYNLISAQGEVNSDAKCHYAALAYICLQVRSVSMNQTEASDLRNFLETPILANDALASEQLLGSKKAKS";
	// char *aa="ASQLA";

	size_t aal=strlen(aa);
	printf("aa length=%zu\n", aal); 
	int i=0, j;

	for(;aa[i++]!='\0';) {
		oc[aa[i-1]-65]++;
		putchar(aa[i-1]);
	}
	printf("\n"); 

	for(i=0;i<26;++i) 
		printf("%i - ", oc[i]);
	printf("\n"); 

	int ocsz=0;
	int gb=GBUF;
	oc_t *ocs=calloc(gb, sizeof(oc_t));

	unsigned char seenc;
	for(i=0; aa[i]!='\0'; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa[i]== ocs[j].l) {
				seenc=1;
				ocs[j].q++;
				break;
			}
		}
		if(seenc==0) {
			if(ocsz==gb-1) {
				gb+=GBUF;
				ocs=realloc(ocs, gb*sizeof(oc_t));
				for(j=gb-GBUF; j<gb; j++)
					ocs[j].q=0;
			}
			ocs[ocsz].l=aa[i];
			ocs[ocsz].q++;
			ocsz++;
		}
	}
	ocs=realloc(ocs, ocsz*sizeof(oc_t));
	printf("%i aa's were seen\n", ocsz); 
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs[i].q);
	printf("\n"); 
	if(aal%ocsz!=0) {
		printf("Error:length not dvisible by number of different aa's\n"); 
		exit(EXIT_FAILURE);
	}
	// printf("equal quan should be %zu\n", aal/ocsz); 
	free(ocs);
	oc_t *ocs2=calloc(GBUF, sizeof(oc_t));

	occheck(aa, ocs2, &gb, aal/ocsz);

	free(ocs);

	return 0;
}
