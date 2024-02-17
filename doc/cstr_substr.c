#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s = make_cstr("abcdefghijklmn"), s2 = cstr_substr(&s, 4, 6);
    cstr_print(&s2);
    cstr_free_high(2, &s, &s2);
    return 0;
}
