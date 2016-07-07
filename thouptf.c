#include <stdio.h>
#include <locale.h>
// printing witht he thousands separator
int main(void)
{
    setlocale(LC_NUMERIC, "");
    printf("%'d\n", 1123456789);
    return 0;
}
