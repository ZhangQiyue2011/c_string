#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s;
    init_cstr(&s);
    cstr_fgets(&s, stdin);
    bool b = cstr_pop(&s);
    if (b) printf("Failed!\n");
    else printf("True!\n");
    cstr_print(&s);
    cstr_free(&s);
    return 0;
}
