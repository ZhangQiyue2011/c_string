#include "c_string.h"

int main(int argc, char const *argv[])
{
    const c_string s = make_cstr("Hi!\n");
    c_string s2;
    s2 = make_cstr("Hello, world!\n");
    if (s.data != NULL)
    {
        cstr_free(&s);
    }
    if (s2.data != NULL)
    {
        cstr_free(&s2);
    }
    
    return 0;
}
