#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
   /* argument accounting: remember argc, the number of arguments, _includes_ the executable */
    int a= 10;
    if(a==10)
        a=11;
    else if(a==11)
        a=12;
    printf("does the if{} statement always exit after first successful attempt?\n"); 
    printf("i.e. is it pretty opposite to switch{} in this sense (which always needs break();)?\n");
    printf("a is %i\n", a); 
    printf("The answer is yes.\n"); 

   return 0;
}
