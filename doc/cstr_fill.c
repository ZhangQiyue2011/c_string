#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s = make_cstr("abcdefghijklmnopqrst"), s2 = make_cstr("012345678");
    cstr_fill(&s, 11, &s2);
    cstr_print(&s);
    cstr_free_high(2, &s, &s2);
    return 0;
}
