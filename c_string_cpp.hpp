#ifndef C_STRING_CPP_HPP
#define C_STRING_CPP_HPP

extern "C"
{
    #include "c_string_include_headers.h"
}

namespace cstrsp
{
#ifndef C_STRING_H
#define NO_C_STRING_H
#endif
    extern "C"
    {
        #include "c_string.h"
    }
#ifdef NO_C_STRING_H
#undef C_STRING_H
#undef NO_C_STRING_H
#endif
} // namespace c_string_namespace

#endif
