/* I'm introducing this idea of a "tdef"
 * or, in other words, a text-#define
 * which mean that we define a text literal within a C #define macro
 * the idea being that we can quickly render a text file as a #dfine in a c header file
 * called say "mytext_tdef.h"
 * and therefore simply #include this header file in our c program.
 * his saves alot of boilerplate code for reading in text, at expense of having it all as a literal
 * and no way of freeing its memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define T0 "\
Rules for réndering a text file as a *_tdef.h file:\n\
- first line must be #define MYTEXT {quote}{backslash}\n\
- then all the original text file lines should end in {backslash}n{backslash}\n\
- final line should be a simple quote and no backslash\n\
The backslashes ensure all lines are kept in the same #define macro, while\n\
the backslash n's insert a newline where the text has a newline, because #define macro's\n\
ignore newlines when there's a backslash.\
"

int main(int argc, char *argv[])
{
    /* for code-legibility purposes, you could declare as follows:
    const char *txt=T0;
    and then:
    printf("Your \"macrotext\" rendered:\n");
    printf("%s\n", txt); 
    and therefore emphasise its const nature.
    But .. you don't have to either. */

    printf("%s\n", T0); 
    printf("Length of text: %zu\n", sizeof(T0)); 
    printf("but it's unparsed for new lines. You may need strtok() .. or may be not.\n");
    printf("Put simply, it's a basic file slurp.\n"); 

    return 0;
}
