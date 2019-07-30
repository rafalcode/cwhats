/* quick char comp */
#include<stdio.h>
#include<stdlib.h>

#define qccomp(s1, s2, r); \
    *(r)=0; \
    while((*(s1)) && (*(s2))) \
        if(*(s1)++ != *(s2)++) \
            *(r)=1; \
    if((*(s1)) || (*(s2))) \
        *(r)=1;

int qccmp(char *s1, char *s2)
{
    while((*s1) && (*s2))
        if(*s1++ != *s2++) // simplest different occurs, within both s1's iand s2's length
            return 1;

    if((*s1) || (*s2)) // so, s2 already longer than s1, or vice versa, so they're different
        return 1;

    // made it this far? Prize!
	return 0;
}

int main(int argc, char *argv[])
{
    if(argc!=3) {
        printf("two strings to compare, thanks.\n");
        exit(EXIT_FAILURE);
    }

    if(!qccmp(argv[1], argv[2]))
        printf("Strings are the exact same.\n");
    else
        printf("There's a difference in the strings.\n");

    printf("Now use the qccomp macro\n"); 

    int r;
    qccomp(argv[1], argv[2], &r);
    if(!r)
        printf("Strings are the exact same.\n");
    else
        printf("There's a difference in the strings.\n");

    return 0;
}
