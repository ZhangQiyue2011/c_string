#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string a;
    bool b = init_cstr(&a);
    if (b == false)
    {
        cstr_free(&a);
    }
    return 0;
}
