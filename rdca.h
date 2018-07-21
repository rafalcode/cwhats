#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define GBUF 2

#define CONDREALLOC(x, b, c, a, t); \
    if((x)>=((b)-1)) { \
        (b) += (c); \
        (a)=realloc((a), (b)*sizeof(t)); \
		memset(((a)+(b)-(c)), 0, (c)*sizeof(t)); \
    }

typedef unsigned char boole;

typedef struct /* ca_t char type */
{
    char **c;
    unsigned bf;
    unsigned lp1; /* length of word plus one (i.e. includes null char */
} ca_t;

