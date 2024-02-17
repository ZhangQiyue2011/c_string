#include "c_string.h"

int main(int argc, char const *argv[])
{
    c_string s;
    s = make_cstr("Hello");
    printf("%d\n", cstrlen(&s) );
    //
    c_string s2 = make_cstr(", world!\n");
    bool b = cstrcat(&s, &s2);
    if (b) printf("The original string:%s", s.data);
    else printf("String:%s", s.data);
    //
    c_string s3_1, s3_2;
    init_cstr(&s3_1);
    s3_2 = make_cstr("123456abcdef");
    cstrcpy(&s3_1, &s3_2);
    //
    c_string s4_1, s4_2;
    s4_2 = make_cstr("1a2b3c4d");
    init_cstrcpy(&s4_1, &s4_2);
    //
    c_string s5_1, s5_2;
    init_cstr(&s5_1);
    init_cstr(&s5_2);
    printf("%d\n", cstrcmp(&s5_1, &s5_2));
    //
    c_string s6_1 = make_cstr("apple"), s6_2 = make_cstr("app");
    printf("%d\n", cstrcspn(&s6_1, &s6_2));
    //
    c_string s7_1 = make_cstr("apple"), s7_2 = make_cstr("app");
    printf("%d\n", cstrstr(&s7_1, &s7_2) - s7_1.data);
    cstr_free_high(12, &s, &s2, &s3_1, &s3_2, &s4_1, &s4_2, &s5_1, &s5_2, &s6_1, &s6_2, &s7_1, &s7_2);
    return 0;
}
