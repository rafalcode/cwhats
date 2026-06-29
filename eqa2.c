/* eqaa.c equalise an amino acid sequence .. from the Nuritas test */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define ROWSZ 100
#define GBUF 4
#define n 4
#define FLAG unsigned char /* some time also called a boolean */

typedef struct /*oc_t */
{
	char l; // letter
	int q; //quantity
} oc_t;

typedef struct /*oc2_t */
{
	char l; // letter
	int q; //quantity
    int fap; // first appearance L to R
    int lap; // last appearance L to R
} oc2_t;

typedef struct /*a_t */
{
	int *els; // elements of the array
	int sz; //sze
	int gb; // buf
} a_t;

void usage(char *pname)
{
	printf("Program \"%s\" to find smallest subsequence where amino-acid sequence has equal numbers of all AAs.\n", "eqaa");
	return;
}

int cmpocs(const void *ocsa, const void *ocsb) /* compare uoa by occurence */
{
    oc_t *oa = (oc_t*)ocsa; /* cast our void! */
    oc_t *ob = (oc_t*)ocsb; /* cast our void! */
    return oa->l  - ob->l; /* lexicographic character comparison: returns positive if b > a and negative if a > b: i.e. highest values first */
}

int cmpocs2(const void *ocsa, const void *ocsb) /* compare uoa by occurence */
{
    oc_t *oa = (oc_t*)ocsa; /* cast our void! */
    oc_t *ob = (oc_t*)ocsb; /* cast our void! */
    return ob->q  - oa->q; /* compare quanitities */
}

void prtoc(oc_t *ocs, int ocsz)
{
	int i;
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs[i].q);
	printf("\n"); 
	return;
}

oc2_t *convooc(char *aa, size_t aal, oc_t *ocs, int ocsz, int maxq, int *rnsz) // converted ordreed oc
{
	int i, j, nsz;
	for(i=0;i<ocsz;++i)
		if(ocs[i].q <= maxq) {
            nsz=i; // so cut off occurs here, meaning sz is the index (i.e. one lower)
            break;
        }

	oc2_t *oc2=calloc(nsz, sizeof(oc2_t));
	for(i=0;i<nsz;++i) {
		oc2[i].l = ocs[i].l;
		oc2[i].q = ocs[i].q;
		oc2[i].fap = 0;
		oc2[i].lap = 0;
    }

    unsigned char seenc;
	int *runoc=calloc(nsz, sizeof(int)); // running occurences
	for(i=0; i<aal; i++) {
		seenc=0;
		for(j=0;j<nsz;++j)
			if(aa[i]== oc2[j].l) {
                runoc[j]++;
                seenc=1;
                if(runoc[j] ==maxq+1)
			        oc2[j].fap=i;
                else if(runoc[j] == oc2[j].q)
			        oc2[j].lap=i;
                break;
            }
		if(seenc==0)
            continue;
    }
    // edge case, a letter is just one over the max allowed, that means lap=fap;
	for(j=0;j<nsz;++j)
	    if(oc2[j].q ==maxq+1)
            oc2[j].lap = oc2[j].fap;


    printf("Runoc:\n"); 
    for(i=0;i<nsz;++i) 
        printf("%i ", runoc[i]); 
    printf("\n"); 

    free(runoc);
    *rnsz=nsz;
	return oc2;
}

void prtoc2(oc2_t *ocs, int ocsz)
{
	int i;
	for(i=0;i<ocsz;++i)
		printf("%4c", ocs[i].l);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs[i].q);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs[i].fap);
	printf("\n"); 
	for(i=0;i<ocsz;++i)
		printf("%4i", ocs[i].lap);
	printf("\n"); 
	return;
}

int prtnoverreps(oc_t *ocs, int ocsz, int maxq)
{
	int i, novreps=0 /* number of over-representatives */;
	for(i=0; i<ocsz; i++)
		if(ocs[i].q>maxq) {
			novreps+=ocs[i].q -maxq;
		}
	printf("Number by which overrepresented chars exceed %i = %i\n", maxq, novreps);
    printf("iThis is essentially the number of changes required for an equalised AA sequence.\n"); 
	return novreps;
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
	printf("minlet was %c, its quan was %i and it unsorted idx was %i\n", ocs[mnidx].l, ocs[mnidx].q, i); 
	return mnidx;
}

int *minlet2(oc_t *ocs, int ocsz, int novreps, int maxq)
{
	int i, j, k, times;
	int *isched=calloc(novreps, sizeof(int)); // index schedule
	k=0;
	for(i=0; i<ocsz; i++)
		if(ocs[i].q<maxq) {
			times=maxq - ocs[i].q;
			for(j=0;j<times;++j) 
				isched[k++]=i;
		}
	return isched;
}

a_t *catchl(char *aa, int aal) /* ctach Leucine occurrences */
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
	if(aal1 != aal2) {
		printf("Sorry, this comparison only allow equal sized strings.\n"); 
		exit(EXIT_FAILURE);
	}
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

void ocgo(char *aa)
{
	int i, j, ocsz=0;
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
	free(ocs);
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
	// printf("equal quan should be %zu\n", aal/ocsz); 
	*ocs=ocs2;
	*ocsz2=ocsz;
	return;
}

void ocfirst2(char *aa, oc2_t **ocs, int *gbp, size_t aal, int *ocsz2, int maxq)
{
	int i, j, ocsz=0;
	int gb=*gbp;
	oc2_t *ocs2=*ocs;
	ocsz=*ocsz2;
	unsigned char seenc;
	for(i=0; aa[i]!='\0'; i++) {
		seenc=0;
		for(j=0;j<ocsz;++j) {
			if(aa[i]== ocs2[j].l) {
				seenc=1;
				ocs2[j].q++;
                if(ocs2[j].q == maxq+1)
				    ocs2[j].fap = i;
				break;
			}
		}
		if(seenc==0) {
			if(ocsz==gb-1) {
				gb+=GBUF;
				ocs2=realloc(ocs2, gb*sizeof(oc2_t));
				for(j=gb-GBUF; j<gb; j++) {
					ocs2[j].q=0;
					ocs2[j].fap=0;
                }
			}
			ocs2[ocsz].l=aa[i];
			ocs2[ocsz].q++;
			ocsz++;
		}
	}
	ocs2=realloc(ocs2, ocsz*sizeof(oc2_t));
	// printf("equal quan should be %zu\n", aal/ocsz); 
	*ocs=ocs2;
	*ocsz2=ocsz;
	return;
}

int main(int argc, char *argv[])
{
	if(argc!=1) {
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}
	// introduce sequence as string literal
	char *aa="ASQLDRFRVFLGWDNGMMLVYQGNKTYEPWLNCDMASPTLSLVSKKAPKILKAADINTTLQPCLAFFIELLLKGIDNERIPNSGSGGREMGLLAPTYSSEATLVTRENNMMEGVHGFENMQDVEVIKLKLPEGYSDVCHFMFMLAGILYIVYDLQMHMSSERETGKFPNPLSDEEFDNPKVVVTNSFVLLEFTVTGAGARPSEQGQEPHNLGATKGSLAISSKTPEIHKDTNPASAQFEGKHTESDAKGVSNEDVFITKERDGREVEPTIKLSKKSVLNPMNVVYNPMLQISEGALRKHSMNDEITILNNTLINKERSVDLGAVSFVNDLLIDKLGCVSGKLAVQLNQSAPPEILHGKDPLTLFLGNTIALMLSKMQRIRVWEEYIFLNLHLALAWEPLLGNLKTHDSQKKWALCGFLIISRIRNLFESEGPVHGLRFSAMPCNTDTRQIKALERFPYAPEKPQWHGDELESPCRLVVASKLLASHDGVSIGKTIGSWPLPAQRYNAYVAWAANDSSILSARPGFAVKEDRLGHSLAQESGTIVVRNPQYGVRFINYNKDEHREFKREATFYPKTVVTHLGAIEGTLMFEIGDAAFTMLHLEEATDAEVRELYYMDMLDKKSSLGRACERIRRVLAPGDHKANGLESAIVSGQNGYEGRIRGLQTFQSNPLKKGRTHMAFCTTLHPFGGLKLVSSQLLKKELAVGTYGHQRTVLHSAEYSCPTSIPNLEGLMYNLISAQGEVNSDAKCHYAALAYICLQVRSVSMNQTEASDLRNFLETPILANDALASEQLLGSKKAKS";
	// char *aa="ASQLDRFRVFLGWDNGMMLVYQGNKTYEPWLNCDMA";

	size_t aal=strlen(aa);
	printf("aa length=%zu\n", aal); 

	int ocsz=0;

	// first pass
	int gb=GBUF;
	oc_t *ocs=calloc(gb, sizeof(oc_t));
	ocfirst(aa, &ocs, &gb, aal, &ocsz);
	if(aal%ocsz!=0) {
		printf("Error:length not dvisible by number of different aa's\n"); 
		exit(EXIT_FAILURE);
	}
	int maxq=aal/ocsz;

    qsort(ocs, ocsz, sizeof(oc_t), cmpocs2);

	prtoc(ocs, ocsz);

    // void convooc(char *aa, size_t aal, oc_t *ocs, int ocsz, int maxq) // converted ordreed oc
    int nsz;
	oc2_t *oc2 = convooc(aa, aal, ocs, ocsz, maxq, &nsz);

	prtoc2(oc2, nsz);

    // calc
    int i, fch=aal-1, lch=0; // first and last changes initial values
    for(i=0;i<nsz;++i) {
        if(oc2[i].fap<fch)
            fch=oc2[i].fap;
        if(oc2[i].lap>lch)
            lch=oc2[i].lap;
    }
    printf("lch=%i - fch=%i + 1 = %i\n", lch, fch, lch-fch +1); 

	free(ocs);
	free(oc2);

	return 0;
}
