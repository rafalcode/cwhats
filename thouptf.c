#include <stdio.h>
#include <string.h>
#include <locale.h>
// printing witht he thousands separator
int main(void)
{
    int i;
    setlocale(LC_NUMERIC, "");
    printf("%'d\n", 1123456789);
    char *names[2]={"dataset", "thisonedataset"};
    int g,maxstr=0;
    for(i=0;i<2;++i) 
        if( (g=(int)strlen(names[i])) > maxstr)
                maxstr=g;
    printf("We use %%-*s to left justify texti, and also sze the string accoring to the max size of rownames\n"); 
    printf("%-*s\t%20s\t%15s\t%10s\n", maxstr, names[0], "num1", "num2", "num3");
    printf("%-*s\t%'20i\t%'15i\t%'10i\n", maxstr, names[1], 45342, 32434, 34231); 
    return 0;
}
