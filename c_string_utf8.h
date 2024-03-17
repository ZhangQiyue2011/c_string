#ifndef C_STRING_UTF8_H
#define C_STRING_UTF8_H
#include "c_string.h"
#include <stdint.h>

int read_char(const char *s)
{
    if ((*s & 0x80) == 0)
    { // 1字节, U+0000 to U+007F
        return 1;
    }
    else if ((*s & 0xE0) == 0xC0)
    { // 2字节, U+0080 to U+07FF
        return 2;
    }
    else if ((*s & 0xF0) == 0xE0)
    { // 3字节, U+0800 to U+FFFF
        return 3;
    }
    else if ((*s & 0xF8) == 0xF0)
    { // 4字节, U+10000 to U+10FFFF
        return 4;
    }
    else
    {
        // 无效的UTF-8开头字节
        // fprintf(stderr, "Invalid UTF-8 character start\n");
        return -1;
    }
}

typedef struct size_value_wchar
{
    int32_t value;
    char size;
} size_value_wchar;

bool error_size(char size)
{
    return size & 0x80;
}

size_value_wchar read_char_check(c_string *s, size_t sub)
{
    size_t len = cstrlen(s);
    int32_t bytes, ch = 0;
    if ((s->data[sub] & 0x80) == 0)
    { // 1字节, U+0000 to U+007F
        ch = s->data[sub];
        bytes = 1;
    }
    else if ((s->data[sub] & 0xE0) == 0xC0)
    { // 2字节, U+0080 to U+07FF
        ch = s->data[sub] & 0x1F;
        bytes = 2;
    }
    else if ((s->data[sub] & 0xF0) == 0xE0)
    { // 3字节, U+0800 to U+FFFF
        ch = s->data[sub] & 0x0F;
        bytes = 3;
    }
    else if ((s->data[sub] & 0xF8) == 0xF0)
    { // 4字节, U+10000 to U+10FFFF
        ch = s->data[sub] & 0x07;
        bytes = 4;
    }
    else
    {
        // 无效的UTF-8开头字节
        // fprintf(stderr, "Invalid UTF-8 character start\n");
        size_value_wchar res;
        res.size = -1;
        return res;
    }
    if (sub + bytes > len)
    {
        size_value_wchar res;
        res.size = -2;
        return res;
    }

    for (int32_t i = 1; i < bytes; i++)
    {
        if ((s->data[sub + i] & 0xC0) != 0x80)
        {
            // 无效的UTF-8后续字节
            size_value_wchar res;
            res.size = -3;
            return res;
        }
        ch = (ch << 6) | (s->data[sub + i] & 0x3F);
    }
    if ((ch >= 0xD800 && ch <= 0xDFFF) || ch > 0x10FFFF)
    {
        size_value_wchar res;
        res.size = -4;
        return res;
    }
    size_value_wchar res;
    res.size = bytes;
    res.value = ch;
    return res;
}

size_t cstr_utf8_seek(c_string *s, size_t start, size_t size)
{
    char step;
    size_t end = start + size, i;
    for (i = start; i < end;)
    {
        step = read_char_check(s, start + i).size;
        if (error_size(step))
        {
            return -1;
        }
        i += step;
    }
    return i;
}

bool cstr_utf8_reverse(c_string *dst, c_string *src)
{
    size_t srclen = cstrlen(src), src_p = 0, dst_p = srclen;
    printf("%d\n", srclen);
    if (srclen >= dst->capa)
    {
        if (cstr_recapa(dst, srclen + 1))
        {
            return true;
        }
        
    }
    
    char step;
    for (; src_p < srclen;)
    {
        step = read_char_check(src, src_p).size;
        if (error_size(step))
        {
            return true;
        }
        dst_p -= step;
        for (char i = 0; i < step; ++i)
        {
            dst->data[dst_p + i] = src->data[src_p + i];
        }
        src_p += step;
    }
    dst->data[srclen] = '\0';
    return false;
}

#endif
