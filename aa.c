#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define ROWSZ 100
#define GBUF 4
#define n 4
#define FLAG unsigned char /* some time also called a boolean */

typedef struct  /* optstruct, a container struct for the options */
{
	FLAG gflg;
} optstruct;

typedef struct /*oc_t */
{
	char l; // letter
	int q; //quantity
} oc_t;

typedef struct /*oc_t */
{
	int *els; // elements of the array
	int sz; //sze
	int gb; // buf
} a_t;

void usage(char *pname)
{
	printf("Program \"%s\" to find smallest subsequence where amino-acid sequence has equal numbers of all AAs.\n");
	return;
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

void prtnoverreps(oc_t *ocs, int ocsz, int maxq)
{
	int i, novreps=0 /* number of over-representatives */;
	for(i=0; i<ocsz; i++)
		if(ocs[i].q>maxq) {
			novreps+=ocs[i].q -maxq;
		}
	printf("Number by which overrepresented chars exceed %i = %i\n", maxq, novreps);
	return;
}

int minlet(oc_t *ocs, int ocsz, int maxq)
{
	int i;
	int mn=maxq;
	int mnidx;
	for(i=0; i<ocsz; i++)
		if(ocs[i].q<mn) {
			mn=ocs[i].q;
			mnidx=i;
		}
	return mnidx;
}

a_t *catchl(char *aa, int aal)
{
	int i;
	a_t *arr=malloc(sizeof(a_t));
	arr->gb=GBUF;
	arr->sz=0;
	arr->els=malloc(arr->gb*sizeof(int));
	for(i=0;i<aal;++i)
		if(aa[i]=='L') {
			if(arr->sz == arr->gb-1) {
				arr->gb+=GBUF;
				arr->els=realloc(arr->els, arr->gb*sizeof(int));
			}
			arr->els[arr->sz]=i;
			arr->sz++;
		}
	arr->els=realloc(arr->els, arr->sz*sizeof(int));

	printf("Here are the positions of the L's\n"); 
	for(i=0;i<arr->sz;++i) 
		printf("%i ", arr->els[i]);
	printf("\n"); 

	return arr;
}

int *cleverroute(char *aa, int aal)
{
	int i, ib, ie, j, kb /* k beginning */, ke /* k end */, k, ocsz=0;
	a_t *arrl=catchl(aa, aal);
	int *ia=malloc(aal*sizeof(int)); // index array
	ib=0;
	ie=aal-1;
	j=0;
	kb=0;
	ke=arrl->sz-1;
	// int bwin=0, ewin=0;
	for(;;) {
		if(j>aal)
			break;
		if(arrl->els[kb]-ib > 2+ie-arrl->els[ke]) {
			for(i=ib;i<=arrl->els[kb];++i) 
				ia[j++]=i;
			ib=1+arrl->els[kb];
			kb++;
		// } else if(arrl->els[kb]-ib <= ie-arrl->els[ke]) {
		} else {
			for(i=ie;i>=arrl->els[ke];--i) 
				ia[j++]=i;
			ie=arrl->els[ke]-1;
			ke--;
		}
	}
	printf("\n"); 
	free(arrl->els);
	free(arrl);
	return ia;
}


void printaaoc(char *aa, oc_t *ocs2, int ocsz)
{
	int i;
	printf("%i aa's were seen\n", ocsz); 
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 

	return;
}

void printcmp2str(char *aa, char *aa2)
{
	int i, j;
	size_t aal1=strlen(aa);
	size_t aal2=strlen(aa2);
	int numchnks=aal1/ROWSZ;
	int partchnk=aal1%ROWSZ;
	for(i=0;i<aal1;++i) 
		if(aa[i]==aa2[i])
			aa2[i]='.';
	if(partchnk)
		numchnks++;
	int *chnka=calloc(numchnks, sizeof(int));
	for(i=0;i<numchnks-1;++i) 
		chnka[i]=ROWSZ;
	chnka[numchnks-1]=(partchnk)?partchnk:ROWSZ;
	for(i=0;i<numchnks;++i) {
		for(j=0;j<chnka[i];++j)
			putchar(aa[i*ROWSZ+j]);
		printf("\n"); 
		for(j=0;j<chnka[i];++j)
			putchar(aa2[i*ROWSZ+j]);
		printf("\n\n"); 
	}

	free(chnka);
	return;
}

void ocfirst(char *aa, oc_t **ocs, int *gbp, size_t aal, int *ocsz2)
{
	int i, j, ocsz=0;
	int gb=*gbp;
	oc_t *ocs2=*ocs;
	ocsz=*ocsz2;
	unsigned char seenc;
	for(i=0; aa[i]!='\0'; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa[i]== ocs2[j].l) {
				seenc=1;
				ocs2[j].q++;
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
	ocs2=realloc(ocs2, ocsz*sizeof(oc_t));
	printf("%i aa's were seen\n", ocsz); 
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 
	if(aal%ocsz!=0) {
		printf("Error:length not dvisible by number of different aa's\n"); 
		exit(EXIT_FAILURE);
	}
	// printf("equal quan should be %zu\n", aal/ocsz); 
	*ocs=ocs2;
	*ocsz2=ocsz;
	return;
}

char *occheckdynbe(char *aa, int aal, oc_t **ocs, int *gbp, int mxq, int *firstch, int *lastch, int *nchanges) // check from both endds .. dynamically.
{
	/* in this version we jump from one end of the string to the other in an attempt to corral in the substring from both sides */
	int i, j, k, ocsz=0;
	// a_t *arrl=catchl(aa, aal);
	int *ia=cleverroute(aa, aal);
	for(i=0;i<aal;++i) 
		printf("%i ", ia[i]); 
	printf("\n"); 
	char *aa2=malloc((aal+1)*sizeof(char));

	FLAG firstchangeeven, nolastch;
	strcpy(aa2, aa);
	int gb=*gbp;
	oc_t *ocs2=*ocs;
	unsigned char seenc;
	*nchanges=0;
	for(i=0; i<aal; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa2[ia[i]]== ocs2[j].l) {
				seenc=1;
				if(ocs2[j].q == mxq) {
#ifdef DBG
					printf("Max quan found at %i with %c\n", ia[i], ocs2[j].l); 
#endif
					k=minlet(ocs2, ocsz, mxq);
#ifdef DBG
					printf("minchar %c:%i\n", ocs2[k].l, ocs2[k].q);
#endif
					aa2[ia[i]]=ocs2[k].l;
					ocs2[k].q++;
					if(*nchanges==0) {
						*firstch=ia[i];
						firstchangeeven=(i%2)?0:1; // note how I work here with i, not ia[i] because i have in mind how to deal with evens and unevens
						nolastch=1;
					} else if( (!firstchangeeven) & nolastch & !(i%2)) {
						*lastch=ia[i]; // last change in this case need much cleverer calculation it the next opposit change!
						nolastch=0;
					} else if( firstchangeeven & nolastch & (i%2)) {
						*lastch=ia[i]; // last change in this case need much cleverer calculation it the next opposit change!
						nolastch=0;
					}
					(*nchanges)++;
				} else
					ocs2[j].q++;
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
			ocs2[ocsz].l=aa2[ia[i]];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	ocs2=realloc(ocs2, ocsz*sizeof(oc_t));
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 
	*ocs=ocs2;
	aa2[aal]='\0';
	free(ia);
	return aa2;
}

char *occheckbe(char *aa, int aal, oc_t **ocs, int *gbp, int mxq, int *firstch, int *lastch, int *nchanges) // check from both ends
{
	/* in this version we jump from one end of the string to the other in an attempt to corral in the substring from both sides */
	int i, j, k, ocsz=0;
	char *aa2=malloc((aal+1)*sizeof(char));
	int *ia=malloc(aal*sizeof(int)); // index array
	j=0;
	int halfway=aal/2;
	for(i=aal-1;i>=halfway;i--) {
		ia[j]=i;
		j+=2;
	}
	j=1;
	for(i=0;i<halfway;i++) {
		ia[j]=i;
		j+=2;
	}
	FLAG firstchangeeven, nolastch;
	strcpy(aa2, aa);
	int gb=*gbp;
	oc_t *ocs2=*ocs;
	unsigned char seenc;
	*nchanges=0;
	for(i=0; i<aal; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa2[ia[i]]== ocs2[j].l) {
				seenc=1;
				if(ocs2[j].q == mxq) {
#ifdef DBG
					printf("Max quan found at %i with %c\n", ia[i], ocs2[j].l); 
#endif
					k=minlet(ocs2, ocsz, mxq);
#ifdef DBG
					printf("minchar %c:%i\n", ocs2[k].l, ocs2[k].q);
#endif
					aa2[ia[i]]=ocs2[k].l;
					ocs2[k].q++;
					if(*nchanges==0) {
						*firstch=ia[i];
						firstchangeeven=(i%2)?0:1; // note how I work here with i, not ia[i] because i have in mind how to deal with evens and unevens
						nolastch=1;
					} else if( (!firstchangeeven) & nolastch & !(i%2)) {
						*lastch=ia[i]; // last change in this case need much cleverer calculation it the next opposit change!
						nolastch=0;
					} else if( firstchangeeven & nolastch & (i%2)) {
						*lastch=ia[i]; // last change in this case need much cleverer calculation it the next opposit change!
						nolastch=0;
					}
					(*nchanges)++;
				} else
					ocs2[j].q++;
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
			ocs2[ocsz].l=aa2[ia[i]];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	ocs2=realloc(ocs2, ocsz*sizeof(oc_t));
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 
	*ocs=ocs2;
	aa2[aal]='\0';
	free(ia);
	return aa2;
}

char *occheckrev(char *aa, int aal, oc_t **ocs, int *gbp, int mxq, int *firstch, int *lastch, int *nchanges)
{
	int i, j, k, ocsz=0;
	char *aa2=malloc((aal+1)*sizeof(char));
	strcpy(aa2, aa);
	int gb=*gbp;
	oc_t *ocs2=*ocs;
	unsigned char seenc;
	*nchanges=0;
	for(i=aal-1; i>=0; i--) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa2[i]== ocs2[j].l) {
				seenc=1;
				if(ocs2[j].q == mxq) {
#ifdef DBG
					printf("Max quan found at %i with %c\n", i, ocs2[j].l); 
#endif
					k=minlet(ocs2, ocsz, mxq);
#ifdef DBG
					printf("minchar %c:%i\n", ocs2[k].l, ocs2[k].q);
#endif
					aa2[i]=ocs2[k].l;
					ocs2[k].q++;
					if(*nchanges==0)
						*firstch=i;
					*lastch=i;
					(*nchanges)++;
				} else
					ocs2[j].q++;
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
			ocs2[ocsz].l=aa2[i];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	ocs2=realloc(ocs2, ocsz*sizeof(oc_t));
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 
	*ocs=ocs2;
	aa2[aal]='\0';
	return aa2;
}

char *occheck(char *aa, int aal, oc_t **ocs, int *gbp, int mxq, int *firstch, int *lastch, int *nchanges)
{
	int i, j, k, ocsz=0;
	char *aa2=malloc((aal+1)*sizeof(char));
	strcpy(aa2, aa);
	int gb=*gbp;
	oc_t *ocs2=*ocs;
	unsigned char seenc;
	*nchanges=0;
	for(i=0; aa2[i]!='\0'; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa2[i]== ocs2[j].l) {
				seenc=1;
				if(ocs2[j].q == mxq) {
#ifdef DBG
					printf("Max quan found at %i with %c\n", i, ocs2[j].l); 
#endif
					k=minlet(ocs2, ocsz, mxq);
#ifdef DBG
					printf("minchar %c:%i\n", ocs2[k].l, ocs2[k].q);
#endif
					aa2[i]=ocs2[k].l;
					ocs2[k].q++;
					if(*nchanges==0)
						*firstch=i;
					*lastch=i;
					(*nchanges)++;
				} else
					ocs2[j].q++;
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
			ocs2[ocsz].l=aa2[i];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	ocs2=realloc(ocs2, ocsz*sizeof(oc_t));
	printf("%i aa's were seen\n", ocsz); 
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs2[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs2[i].q);
	printf("\n"); 
	*ocs=ocs2;
	aa2[aal]='\0';
	return aa2;
}

int main(int argc, char *argv[])
{
	if(argc!=1) {
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}
	// introduce sequence as string literal
	char *aa="ASQLDRFRVFLGWDNGMMLVYQGNKTYEPWLNCDMASPTLSLVSKKAPKILKAADINTTLQPCLAFFIELLLKGIDNERIPNSGSGGREMGLLAPTYSSEATLVTRENNMMEGVHGFENMQDVEVIKLKLPEGYSDVCHFMFMLAGILYIVYDLQMHMSSERETGKFPNPLSDEEFDNPKVVVTNSFVLLEFTVTGAGARPSEQGQEPHNLGATKGSLAISSKTPEIHKDTNPASAQFEGKHTESDAKGVSNEDVFITKERDGREVEPTIKLSKKSVLNPMNVVYNPMLQISEGALRKHSMNDEITILNNTLINKERSVDLGAVSFVNDLLIDKLGCVSGKLAVQLNQSAPPEILHGKDPLTLFLGNTIALMLSKMQRIRVWEEYIFLNLHLALAWEPLLGNLKTHDSQKKWALCGFLIISRIRNLFESEGPVHGLRFSAMPCNTDTRQIKALERFPYAPEKPQWHGDELESPCRLVVASKLLASHDGVSIGKTIGSWPLPAQRYNAYVAWAANDSSILSARPGFAVKEDRLGHSLAQESGTIVVRNPQYGVRFINYNKDEHREFKREATFYPKTVVTHLGAIEGTLMFEIGDAAFTMLHLEEATDAEVRELYYMDMLDKKSSLGRACERIRRVLAPGDHKANGLESAIVSGQNGYEGRIRGLQTFQSNPLKKGRTHMAFCTTLHPFGGLKLVSSQLLKKELAVGTYGHQRTVLHSAEYSCPTSIPNLEGLMYNLISAQGEVNSDAKCHYAALAYICLQVRSVSMNQTEASDLRNFLETPILANDALASEQLLGSKKAKS";

	size_t aal=strlen(aa);
	printf("aa length=%zu\n", aal); 

	int ocsz=0;

	// first pass
	int gb=GBUF;
	oc_t *ocs=calloc(gb, sizeof(oc_t));
	ocfirst(aa, &ocs, &gb, aal, &ocsz);
	int maxq=aal/ocsz;
	prtnoverreps(ocs, ocsz, maxq);
	free(ocs);

	// second pass
	gb=GBUF;
	int nchanges=0, firstch=0, lastch=0;
	oc_t *ocs2=calloc(gb, sizeof(oc_t));
	//char *aa2=occheck(aa, aal, &ocs2, &gb, aal/ocsz, &firstch, &lastch, &nchanges);
	char *aa2=occheckdynbe(aa, aal, &ocs2, &gb, aal/ocsz, &firstch, &lastch, &nchanges);

	printaaoc(aa2, ocs2, ocsz);
	printcmp2str(aa, aa2);

	printf("Summary: Num changes to input string=%i, first change at %i and last change at %i\n", nchanges, firstch, lastch); 
	int szsub=lastch-firstch+1;
	printf("Length of smallest substring for changes = %i, %2.2f times over the min num changes\n", szsub, (float)szsub/nchanges);

	oc_t *ocs3=calloc(gb, sizeof(oc_t));
	gb=GBUF;
	// char *aa3=occheckbe(aa, aal, &ocs3, &gb, aal/ocsz, &firstch, &lastch, &nchanges); // seemed like a great idea .. but, no.
	// char *aa3=occheckrev(aa, aal, &ocs3, &gb, aal/ocsz, &firstch, &lastch, &nchanges);

	// printaaoc(aa3, ocs3, ocsz);
	// printcmp2str(aa, aa3);

	// printf("Summary: Num changes to input string=%i, first change at %i and last change at %i\n", nchanges, firstch, lastch); 
	// szsub=firstch-lastch+1; // measured this and saw that if you subtract indices or positions you need to add 1.
	// printf("Length of smallest substring for changes = %i, %2.2f times over the min num changes\n", szsub, (float)szsub/nchanges);

	// a_t *arrl=catchl(aa, aal);
	// free(arrl->els);
	// free(arrl);

// 	cleverroute(aa, aal);

	free(ocs2);
	free(aa2);
	// free(ocs3);
	// free(aa3);

	return 0;
}
