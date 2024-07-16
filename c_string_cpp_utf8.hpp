#ifndef C_STRING_CPP_HPP
#define C_STRING_CPP_HPP
#include "c_string_cpp.hpp"

namespace cstrsp
{
#ifndef C_STRING_UTF8_H
#define NO_C_STRING_UTF8_H
#endif
    extern "C"
    {
        #include "c_string_utf8.h"
    }
#ifdef NO_C_STRING_UTF8_H
#undef C_STRING_UTF8_H
#undef NO_C_STRING_UTF8_H
#endif
} // namespace c_string_namespace

#endif
