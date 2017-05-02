#include <stdio.h>
#include <locale.h>
// printing witht he thousands separator
int main(void)
{
    setlocale(LC_NUMERIC, "");
    printf("%'d\n", 1123456789);

    printf("%5.8s\t%'20i\t%'15i\t%'10i\n", "thisset", 45342, 32434, 34231); 
    return 0;
}
