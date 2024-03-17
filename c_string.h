#ifndef C_STRING_H
#define C_STRING_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct c_string
{
    size_t capa;
    char *data;
} c_string;

bool cstr_recapa(c_string *s, size_t size);

void init_cstr(c_string *s)
{
    s->capa = 1;
    s->data = (char *)malloc(sizeof(char));
    if (s->data == NULL)
    {
        return;
    }
    s->data[0] = '\0';
}

c_string make_cstr(const char *c)
{
    c_string s;
    s.capa = strlen(c) + 1;
    s.data = (char *)malloc(s.capa * sizeof(char));
    if (s.data == NULL)
    {
        // fprintf(stderr, "Memory allocation failed!\n");
        return s;
    }
    strcpy(s.data, c);
    return s;
}

c_string make_cstr_set(size_t elements, int data_char)
{
    c_string s;
    s.capa = elements + 1;
    s.data = (char *)malloc(s.capa * sizeof(char));
    if (s.data == NULL)
    {
        // fprintf(stderr, "Memory allocation failed!\n");
        return s;
    }
    memset(s.data, data_char, elements);
    s.data[elements] = '\0';
    return s;
}

c_string make_cstr_chr(char c)
{
    c_string s;
    s.capa = 2;
    s.data = (char *)malloc(2 * sizeof(char));
    if (s.data == NULL)
    {
        return s;
    }
    s.data[0] = c;
    s.data[1] = '\0';
    return s;
}

size_t cstrlen(const c_string *s)
{
    return strlen(s->data);
}

bool cstrcat(c_string *a, const c_string *b)
{
    size_t sz1 = cstrlen(a), sz2 = cstrlen(b);
    size_t fewest_capa = sz1 + sz2 + 1ull;
    if (a->capa < fewest_capa)
    {
        if (cstr_recapa(a, fewest_capa))
        {
            return true;
        }
        
    }
    memcpy(a->data + sz1, b->data, sz2);
    a->data[fewest_capa - 1] = '\0';
    return false;
}

c_string init_cstrcpy(c_string *a, const c_string *b)
{
    if (a != b)
    {
        a->capa = cstrlen(b) + 1ull;
        a->data = (char *)malloc(a->capa * sizeof(char));
        strcpy(a->data, b->data);
    }
    return *a;
}

c_string cstrcpy(c_string *a, const c_string *b)
{
    if (a != b)
    {
        free(a->data);
        a->capa = cstrlen(b) + 1ull;
        a->data = (char *)malloc(a->capa * sizeof(char));
        strcpy(a->data, b->data);
    }
    return *a;
}

int cstrcmp(const c_string *a, const c_string *b)
{
    return strcmp(a->data, b->data);
}

bool cstr_simplify(c_string *s)
{
    size_t sz = cstrlen(s) + 1;
    if (sz == s->capa)
    {
        return false;
    }
    if (cstr_recapa(s, sz))
    {
        return true;
    }
    
    return false;
}

c_string cstr_substr(const c_string *s, size_t start, size_t length)
{
    c_string res;
    res.capa = length + 1;
    res.data = (char *)malloc(res.capa * sizeof(char));
    for (size_t i = 0; i < length; ++i)
    {
        res.data[i] = s->data[i + start];
    }
    res.data[length] = '\0';
    return res;
}

int cstr_print(const c_string *s)
{
    return printf("%s", s->data);
}

int cstr_fprint(FILE *const fl, const c_string *s)
{
    return fprintf(fl, "%s", s->data);
}

// 假设getchar是可用的，但在非标准库环境中，你需要用适合该环境的函数替换它
int cstr_scan(c_string *s)
{
    int ch;
    while ((ch = getchar()) != EOF && isspace(ch))
    { /* 跳过前导空白 */
    }

    if (ch == EOF)
    {
        return EOF; // 如果达到文件末尾，则返回EOF
    }

    int i = 0;
    while (!isspace(ch) && ch != EOF)
    { // 读取直到遇到空白字符或EOF
        if (i == s->capa - 1)
        {
            s->capa <<= 1ull;
            if (cstr_recapa(s, s->capa))
            {
                return -1;
            }
            
        }

        s->data[i++] = (char)ch; // 存储字符到字符串中
        ch = getchar();          // 读取下一个字符
    }
    s->data[i] = '\0'; // 在字符串末尾添加空字符以终止字符串

    // 如果读取了至少一个非空白字符，则返回成功读取的项数（在这种情况下是1）
    // 否则，如果遇到EOF而没有读取任何字符，则返回EOF（但这种情况在上面已经处理过了）
    return i > 0 ? 1 : EOF;
}

int cstr_fscan(FILE *const fl, c_string *s)
{
    int ch;
    while ((ch = getc(fl)) != EOF && isspace(ch))
    { /* 跳过前导空白 */
    }

    if (ch == EOF)
    {
        return EOF; // 如果达到文件末尾，则返回EOF
    }

    int i = 0;
    while (!isspace(ch) && ch != EOF)
    { // 读取直到遇到空白字符或EOF
        if (i == s->capa - 1)
        {
            s->capa <<= 1ull;
            if (cstr_recapa(s, s->capa))
            {
                return -1;
            }
        }

        s->data[i++] = (char)ch; // 存储字符到字符串中
        ch = getc(fl);           // 读取下一个字符
    }
    s->data[i] = '\0'; // 在字符串末尾添加空字符以终止字符串

    // 如果读取了至少一个非空白字符，则返回成功读取的项数（在这种情况下是1）
    // 否则，如果遇到EOF而没有读取任何字符，则返回EOF（但这种情况在上面已经处理过了）
    return i > 0 ? 1 : EOF;
}

int cstr_fgets(c_string *s, FILE *const stream)
{
    size_t i = 0;
    int ch;
    while ((ch = getc(stream)) != EOF && ch != '\n')
    {
        if (i == s->capa - 1)
        {
            s->capa <<= 1ull;
            if (cstr_recapa(s, s->capa))
            {
                return -1;
            }
            
        }

        s->data[i++] = (char)ch;
    }
    if (ch == '\n')
    {
        s->data[i++] = '\n';
    }
    s->data[i] = '\0';
    return i;
}

int cstr_fgetline(c_string *s, FILE *const stream, int delim, bool reserve)
{
    size_t i = 0;
    int ch;
    while ((ch = getc(stream)) != EOF && ch != delim)
    {
        if (i == s->capa - 1)
        {
            s->capa <<= 1ull;
            if (cstr_recapa(s, s->capa))
            {
                return -1;
            }
            
        }

        s->data[i++] = (char)ch;
    }
    if (reserve && ch == delim)
    {
        s->data[i++] = (char)delim;
    }
    s->data[i] = '\0';
    return i;
}

bool cstr_pop(c_string *s)
{
    size_t len = cstrlen(s);
    if (len == 0)
    {
        return true;
    }
    s->data[len - 1] = '\0';
    return false;
}

bool cstr_fill(c_string *a, size_t start, const c_string *b)
{
    size_t sz1 = cstrlen(a), sz2 = cstrlen(b);
    if (sz1 - start < sz2)
    {
        return true;
    }
    // strcpy(a + start, b);
    memcpy(a->data + start, b->data, sz2 * sizeof(char));
    return false;
}

bool cstr_fill_unsafe(c_string *a, size_t start, const c_string *b)
{
    size_t sz2 = cstrlen(b);
    memcpy(a->data + start, b->data, sz2 * sizeof(char));
    return false;
}

bool cstr_fill_unsafe_capacity(c_string *a, size_t start, const c_string *b)
{
    size_t sz1 = cstrlen(a), sz2 = cstrlen(b), sz, capa;
    if (start + sz2 > sz1)
    {
        sz = sz2 + start;
        capa = sz + 1;
        if (capa > a->capa)
        {
            if (cstr_recapa(a, capa))
            {
                return true;
            }
            
        }
        memcpy(a->data + start, b->data, sz2 * sizeof(char));
        a->data[sz] = '\0';
        return false;
    }
    sz = sz1;
    capa = sz + 1;
    memcpy(a->data + start, b->data, sz2 * sizeof(char));
    return false;
}

bool cstr_reserve(c_string *s, size_t start, size_t length)
{
    size_t sz = cstrlen(s), sz2 = sz + length + 1;
    if (sz2 > s->capa)
    {
        if (cstr_recapa(s, sz2))
        {
            return true;
        }
        
    }
    if (sz - start < length)
    {
        memset(s->data + sz, s->data[start], length + start - sz);
    }
    memmove(s->data + start + length, s->data + start, sz);
    s->data[sz + length] = '\0';
    return false;
}

bool cstr_reserve_unsafe(c_string *s, size_t start, size_t length)
{
    size_t sz = cstrlen(s), sz2 = sz + length + 1;
    if (sz2 > s->capa)
    {
        if (cstr_recapa(s, sz2))
        {
            return true;
        }
        
    }
    /*if (sz - start < length)
    {
        memset(s->data + sz, s->data[start], length + start - sz);
    }*/
    /*size_t sz_start = sz - start;
    for (size_t i = 0; i < sz_start; ++i)
    {
        s->data[sz - i - 1 + length] = s->data[sz - i - 1];
    }*/
    memmove(s->data + start + length, s->data + start, sz);
    s->data[sz + length] = '\0';
    return false;
}

bool cstr_delete(c_string *s, size_t start, size_t length)
{
    size_t sz = cstrlen(s);
    if (start >= sz || start + length > sz)
    {
        return true;
    }
    size_t startplength = start + length;
    for (size_t i = startplength; i < sz; ++i)
    {
        s->data[i - length] = s->data[i];
    }
    s->data[sz - length] = '\0';
    return false;
}

bool cstr_recapa(c_string *s, size_t size)
{
    char *new_data = (char *)realloc(s->data, size * sizeof(char));
    if (new_data == NULL)
    {
        return true;
    }
    s->data = new_data;
    s->capa = size;
    return false;
}

void cstr_pull(c_string *s, const char *c)
{
    size_t the_fewest_capa = strlen(c) + 1;
    if (s->capa < the_fewest_capa)
    {
        if (cstr_recapa(s, the_fewest_capa))
        {
            return;
        }
        
    }
    strcpy(s->data, c);
}

void cstr_pull_set(c_string *s, size_t elements, int data_char)
{
    if (s->capa <= elements)
    {
        if (cstr_recapa(s, elements + 1))
        {
            return;
        }
    }
    memset(s->data, data_char, elements);
    s->data[elements] = '\0';
}

void cstr_pull_chr(c_string *s, char c)
{
    if (s->capa < 2)
    {
        if (cstr_recapa(s, 2))
        {
            return;
        }
    }
    s->data[0] = c;
    s->data[1] = '\0';
}

size_t cstr_find(const c_string *s, const c_string *sub)
{
    size_t str_len = cstrlen(s), substr_len = cstrlen(sub);
    if (substr_len == 0)
    {
        return 0;
    }
    if (str_len < substr_len)
    {
        return -1;
    }
    for (size_t i = 0; i <= str_len - substr_len; ++i)
    {
        size_t j;
        for (j = 0; j < substr_len; ++j)
        {
            if (s->data[i + j] != sub->data[j])
            {
                goto find_label;
            }
        }
        return i;
    find_label:
    }
    return -1;
}

size_t cstr_rfind(const c_string *s, const c_string *sub)
{
    size_t str_len = cstrlen(s), substr_len = cstrlen(sub);
    if (substr_len == 0)
    {
        return str_len - 1;
    }
    if (str_len < substr_len)
    {
        return -1;
    }
    for (size_t i = str_len - substr_len; i != (size_t)-1; --i)
    {
        size_t j;
        for (j = 0; j < substr_len; ++j)
        {
            if (s->data[i + j] != sub->data[j])
            {
                goto rfind_label;
            }
        }
        return i;
    rfind_label:
    }
    return -1;
}

size_t find_first_of(const c_string *s, char ch)
{
    size_t str_len = cstrlen(s);
    if (str_len == 0)
    {
        return -1;
    }
    for (size_t i = 0; i < str_len; ++i)
    {
        if (s->data[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

size_t find_last_of(const c_string *s, char ch)
{
    size_t str_len = cstrlen(s);
    if (str_len == 0)
    {
        return -1;
    }
    for (size_t i = str_len - 1; i != (size_t)-1; --i)
    {
        if (s->data[i] == ch)
        {
            return i;
        }
    }
    return -1;
}

void cstr_reverse(c_string *s)
{
    for (size_t i = 0, j = cstrlen(s) - 1; i < j; ++i, --j)
    {
        s->data[i] = s->data[i] ^ s->data[j];
        s->data[j] = s->data[j] ^ s->data[i];
        s->data[i] = s->data[i] ^ s->data[j];
    }
}

bool cstr_isempty(c_string *s)
{
    return s->data[0] == '\0';
}

void cstr_clear(c_string *s)
{
    s->data[0] = '\0';
}

void cstr_free(c_string *s)
{
    free(s->data);
}

void cstr_free_high(size_t size, ...)
{
    va_list valist;
    va_start(valist, size);
    for (size_t i = 0; i < size; ++i)
    {
        free(va_arg(valist, const c_string *)->data);
    }
    va_end(valist);
}

#endif
