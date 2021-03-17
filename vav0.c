/* exercise using the variable arguments construct va_list.
from cprogramming, authored by Alex Allain

va_start is a macro which accepts two arguments, a va_list and the name of the variable that directly precedes the ellipsis ("...").

*/
#include <stdarg.h> // this is where the va_list goodies are
#include <stdio.h>

/* this function will take the number of values to average
 *    followed by all of the numbers to average */
double average ( int num, ... )
{
    va_list args;                     
    double sum = 0;
    int x;

    /* Initializing arguments to store all values after the num variable */
    va_start(args, num );           
    /* Sum all the inputs; we still rely on the function caller to tell us how many there are */
    for (x = 0; x < num; x++ )
        sum += va_arg (args, double ); 
    va_end ( args );                  // Cleans up the list

    return sum / num;
}

int main()
{
    /* this computes the average of 13.2, 22.3 and 4.5 (3 indicates the number of values to average) */
    printf( "%f\n", average ( 3, 12.2, 22.3, 4.5 ) );
    /* here it computes the average of the 5 values 3.3, 2.2, 1.1, 5.5 and 3.3 */
    printf( "%f\n", average ( 5, 3.3, 2.2, 1.1, 5.5, 3.3 ) );
}
