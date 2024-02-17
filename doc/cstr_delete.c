#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s = make_cstr("Hello, Welcome world!\n");
    cstr_delete(&s, 7, 8);
    cstr_print(&s);
    cstr_free(&s);
    return 0;
}
