#include <stdio.h>

// exercises from codewars

void tn(char *te, int *nums)
{
    int i;
    te[0]='(';
    for(i=1;i<4;++i) 
        te[i]=48+i-1;
    te[4]=')';
    te[5]=' ';
    for(i=6;i<9;++i) 
        te[i]=48+i-3;
    te[9]='-';
    for(i=10;i<14;++i) 
        te[i]=48+i-4;
    return;
}

char *tn2(char *te, int *nums)
{
    // note how there seems to be redundancy here, the output array te is in the args and is also returned.
    // this works. What won;t work is defining it in the function and returning it, which as it's local, is not allowed.
    int i;
    te[0]='(';
    for(i=1;i<4;++i) 
        te[i]=48+i-1;
    te[4]=')';
    te[5]=' ';
    for(i=6;i<9;++i) 
        te[i]=48+i-3;
    te[9]='-';
    for(i=10;i<14;++i) 
        te[i]=48+i-4;
    return te;
}

char *tn0(char *te, int *nums)
{
    int i, j=0;
    for(i=0;i<14;++i) 
        // this won't work because indices are not in 1 to 1 corresp.
        // does work now because of j free incrementing variable.
        switch(i) {
            case 0: te[i]='('; break;
            case 4: te[i]=')'; break;
            case 5: te[i]=' '; break;
            case 9: te[i]='-'; break;
            default: te[i]=48+nums[j++];
        }
    return te;
}

int main(int argc, char *argv[])
{
    int n[10]={0, 1,2,3,4,5,6,7,8,9};
    int i;
    char ns[11]={0};
    for(i=0;i<10;++i) 
        ns[i]=48+n[i];
    printf("(%.*s) %.*s-%.*s\n", 3, ns, 3, ns+3, 4, ns+6);
    // following won't work it's pretty much a string only thing.
    // printf("(%.*i) %.*i-%.*i\n", 3, *n, 3, *(n+3), 4, *(n+6));
    // printf("(%.*c) %.*c-%.*c\n", 3, ns, 3, ns+3, 4, ns+6);
    char te[15]={0};
    printf("%s\n", tn0(te, n)); // keep getting a valgrind error here
    // printf("%s\n", te);

   return 0;
}
