#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 0; //make it as global variable

void func(int *a, int idx)
{
   for (a[idx] = 0; a[idx] < 3; a[idx]++) {
       if (idx != 0) {
           func(a, (idx - 1));
           putchar('\n');
       } else {
           i++;
           putchar(a[a[idx]]);
       }
   }
   return;
}


int main(int argc, char *argv[])
{
    // int a[4]={'A', 'C', 'G', 'T'};
    int a[4]={0};
    func(a, 3);

   return 0;
}
