#include "rdca.h" // has the header stuff, and structs.

ca_t *crea_ca(void)
{
    ca_t *ca=malloc(sizeof(ca_t));
    ca->lp1=0;
    ca->bf=GBUF;
    ca->c=malloc(sizeof(char*));
    (*ca->c)=malloc(ca->bf*sizeof(char));
    memset((*ca->c), 0, ca->bf*sizeof(char)); // no fun to use calloc()
    return ca;
}

void grow_ca(ca_t *ca, unsigned buf)
{
    ca->bf += buf;
    unsigned diffsz = ca->bf - ca->lp1;
    (*ca->c)=realloc((*ca->c), ca->bf*sizeof(char));
    memset((*ca->c)+ca->lp1, 0, diffsz*sizeof(char));
    return;
}

void condgrow_ca(ca_t *ca, unsigned buf, unsigned idx)
{
    unsigned diffsz;
    if(idx >= ca->bf-1) {
        ca->bf += buf;
        diffsz = ca->bf - ca->lp1;
        (*ca->c)=realloc((*ca->c), ca->bf*sizeof(char));
        // memset((*ca->c)+ca->lp1, 0, diffsz*sizeof(char));
        memset((*ca->c)+ca->bf-buf, 0, buf*sizeof(char));
    }
    return;
}

void norm_ca(ca_t *ca)
{
    (*ca->c)=realloc((*ca->c), ca->lp1*sizeof(char));
    ca->bf = ca->lp1;
    return;
}

void reset_ca(ca_t *ca)
{
    ca->lp1=0;
    ca->bf=GBUF;
    (*ca->c)=realloc((*ca->c), ca->bf*sizeof(char));
    memset((*ca->c), 0, ca->bf*sizeof(char));
    return;
}

void free_ca(ca_t *ca)
{
    free((*ca->c));
    free(ca->c);
    free(ca);
    return;
}

ca_t *process_w1(char *fname)
{
    /* declarations */
    FILE *fp=fopen(fname,"r");
    unsigned couc /*count chars per line */;
    int c;
    boole inword;

    ca_t *ca=crea_ca(); 
    couc=0;
    inword=0;

    for(;;) {
        c=fgetc(fp);
        putchar(c);
        if(c== ' ')
            break;
        inword=1;
        condgrow_ca(ca, GBUF, couc);
        (*ca->c)[couc]=(char)c;
        couc++;
    }
    inword=0;
    (*ca->c)[couc++]='\0';
    ca->lp1=couc;
    // norm_ca(ca);
    fclose(fp);
    return 0;
}

void prtusage(void)
{
    printf("Usage notice. Very much a test program, reads first word from a file.\n");
    return;
}

int main(int argc, char *argv[])
{
    /* argument accounting */
    if(argc!=2) {
        prtusage();
        exit(EXIT_FAILURE);
    }

    ca_t *ca=process_w1(argv[1]);
    // printf("%s\n", (*ca->c)); 

    free_ca(ca);
    return 0;
}
