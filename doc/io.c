#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s1, s2, s3;
    init_cstr(&s1);
    init_cstr(&s2);
    init_cstr(&s3);
    cstr_scan(&s1);
    cstr_fscan(&s2, stdin);
    cstr_fgets(&s3, stdin);
    cstr_print(&s1);
    cstr_print(&s2);
    cstr_print(&s3);
    cstr_free_high(3, &s1, &s2, &s3);
    return 0;
}
