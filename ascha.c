/* have a look at 
 *
 * https://stackoverflow.com/questions/11614050/can-i-initialize-string-after-declaration
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{

   /* declarations */
   char str[3];
   // str={'r', '1', '\0'};
   for(int i=0;i<3;++i) 
       str[i]='\0';

   /* print stuff out */
   printf("Res_1: %s\n", str);

   return 0;
}
