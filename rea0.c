/* simple realloc() exercises */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SZ 16

int main(int argc, char *argv[])
{

   /* let's declare a pointer to char and initialise as NULL,
    * because valgrindlkes you to do that, and you like valgrind */
   char *tc=NULL;

   /* now let's allocate memory, but not via the usual malloc or calloc,
      no we'use realloc() which is caable of allocating memory,
      even if there's no memory there to start with */
   tc=realloc(tc, SZ*sizeof(char));
   /* OK, an we also want to initialise it. Of course this can all be done
      with calloc() but that's not the point of this exercise. */
   memset(tc, 0, sizeof(char));
   /* OK, let's put some random string into it now */
   strcpy(tc, "thisaway");

   /* it'll print out as a normal %s on printf: */
   printf("%s\n", tc); 

   /* and now let's increase its size .. this is the mmore conventonal use of realloc() */
   tc=realloc(tc, 2*SZ*sizeof(char));
   /* now we're going to wipe it clean, but actually we're only goingto change the first
    * character .. can you see that? */
   memset(tc, 0, sizeof(char));
   /* so what will strcpy do? I guess it will overwrite, yes, pretty much */
   strcpy(tc, "thataway");

   printf("%s\n", tc); 

   free(tc);

   /* silly exercise over */
   return 0;
}
