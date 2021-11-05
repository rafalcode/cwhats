#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int comp(const int *a, const int *b, int n)
{
    if(!n)
        return 0;
    int i, j, sq;
    unsigned char mi;
    unsigned char *c=calloc(n, sizeof (unsigned char));

    for(i=0;i<n;++i) {
        mi=0;
        sq=a[i]*a[i];
        for(j=0;j<n;++j) {
            if(c[j])
                continue;
            if(sq==b[j]) {
                c[j]=1;
                mi=1;
                break;
            }
        }
        if(!mi) {
            printf("i:%i,%i,%i\n", i, a[i], a[i]*a[i]); 
            return 0;
        }
    }

    int sum=0;
    for(i=0;i<n;++i) {
        // printf("%i\n", c[i]); 
        sum+=c[i];
    }
    // printf("\n"); 
    if(sum!=n)
        return 0;

    free(c);
    return 1;
}

int main(int argc, char *argv[])
{
    int a[9]={121, 144, 19, 161, 19, 144, 19, 11, 1008};
    int b[9]={14641, 20736, 361, 25921, 361, 20736, 361, 121, 12340};
    // int a[8] = {121, 144, 19, 161, 19, 144, 19, 11};
    // int b[8] = {121, 14641, 20736, 361, 25921, 361, 20736, 361};
    printf("%s\n", (comp(a, b, 9))?"same":"wrong");
   return 0;
}
