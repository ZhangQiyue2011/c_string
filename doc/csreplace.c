#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string a, b;
    init_cstr(&a);
    init_cstr(&b);
    cstr_fgets(&a, stdin);
    cstr_fgets(&b, stdin);
    size_t start, length, sza = cstrlen(&a), szb = cstrlen(&b);
    if (szb != 0 && b.data[szb - 1] == '\n')
    {
        b.data[szb - 1] = '\0';
        --szb;
    }
    scanf("%zu%zu", &start, &length);
    if (szb == length)
    {
        cstr_fill(&a, start, &b);
    }
    else if (szb > length)
    {
        size_t sub = szb - length;
        cstr_reserve(&a, start, sub);
        cstr_fill(&a, start, &b);
    }
    else
    {
        cstr_delete(&a, 16, 6);
        cstr_fill(&a, start, &b);
    }
    
    cstr_print(&a);
    cstr_free_high(2, &a, &b);
    return 0;
}
