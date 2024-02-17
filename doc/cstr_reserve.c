#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s = make_cstr("Hellowo!\n"), r1 = make_cstr(", "), r2 = make_cstr("rld");
    cstr_reserve(&s, 5, 2);
    cstr_fill(&s, 5, &r1);
    cstr_print(&s);
    cstr_reserve(&s, 9, 3);
    cstr_print(&s);
    cstr_fill(&s, 9, &r2);
    cstr_print(&s);
    cstr_free_high(3, &s, &r1, &r2);
    return 0;
}
