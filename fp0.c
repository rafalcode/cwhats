#include <stdio.h>
void my_int_func(int x)
{
    printf( "%d\n", x );
}
 
int main()
{
    // thi sis the nost concise way to declare an djointely define a function pointer.
    void (*foo)(int) =my_int_func;
    
    // foo = &my_int_func;
    foo(4); // of course my_int_func(4); would do the same thing, but that's nto the point. You can _dispatch_ a function pointer to a function, isn't it?
 
    return 0;
}
