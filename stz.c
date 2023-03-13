/* very tricky setting struct tio zero in a macro
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/stat.h>

#define GBUF 4
#define CONDREALLOC0(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(int i=((b)-(c)); i<(b); ++i) { \
            (a)[i].h = 5; \
            (a)[i].m = 5; \
            (a)[i].s = 5; \
            (a)[i].hh = 5; \
        } \
    }

#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
        for(int i=((b)-(c)); i<(b); ++i) { \
            (a)[i] = {5, 5, 5, 5}; \
        } \
    }
// following is like atoi (natoi), but does not require \0 at end, only a simplesequence of chars of size n
#define NATOI(x, cs, n); \
    for(int i=0; i<(n); ++i) \
        (x) += ((int)(cs)[i]-48) * pow(10, ((n)-1-(i)));

typedef struct /* tt_c */
{
    int h, m, s, hh;
} tt_c;

typedef struct /* av_c */
{
    int vbf, vsz;
    tt_c *v;
} av_c;

av_c *crea_avc(int vbf)
{
    av_c *avc=malloc(sizeof(av_c));
    avc->vbf=vbf;
    avc->v=calloc(avc->vbf, sizeof(tt_c));
    avc->vsz=0;
    return avc;
}

void condrea_avc(av_c *avc)
{
    /* somewhat trivial, but idea is that, as avc is a container, it can be re-alloced inside a function */
    CONDREALLOC(avc->vsz, avc->vbf, GBUF, avc->v, tt_c);
    return;
}

void norm_avc(av_c *avc)
{
    avc->v=realloc(avc->v, avc->vsz*sizeof(tt_c));
    return;
}

void free_avc(av_c *avc)
{
    free(avc->v);
    free(avc);
    return;
}

void prtavec(av_c *avc)
{
    int i;
    for(i=0;i<avc->vsz;++i)
        printf("%i:%i:%i:%i\n", avc->v[i].h, avc->v[i].m, avc->v[i].s, avc->v[i].hh); 
    return;
}

int main(int argc, char **argv)
{
    av_c *avc=crea_avc(GBUF);
    avc->vsz=16;
    condrea_avc(avc);

    avc->vsz=12;
    norm_avc(avc);
    prtavec(avc);
    free_avc(avc);
    return 0;
}
