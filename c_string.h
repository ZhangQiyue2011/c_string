#ifndef C_STRING_H
#define C_STRING_H
#include "c_string_include_headers.h"

typedef struct c_string
{
    size_t capa;
    char *data;
} c_string;

typedef size_t len_t;

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

c_string make_cstr_len(const char *c, len_t len)
{
    c_string s;
    s.capa = len + 1;
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

c_string cstr_substr(const c_string *s, size_t start, size_t length, len_t s_len)
{
    c_string res;
    if (start + length > s_len)
    {
        res.data = NULL;
        return res;
    }
    res.capa = length + 1;
    res.data = (char *)malloc(res.capa * sizeof(char));
    memcpy(res.data, s->data + start, length);
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
int cstr_scan(c_string *s, len_t *len)
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
    *len = i;
    return i > 0 ? 1 : EOF;
}

int cstr_fscan(FILE *const fl, c_string *s, len_t *len)
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
    *len = i;
    return i > 0 ? 1 : EOF;
}

int cstr_fgets(c_string *s, FILE *const stream, len_t *len)
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
    *len = i;
    return 1;
}

int cstr_fgetline(c_string *s, FILE *const stream, int delim, bool reserve, len_t *len)
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
    *len = i;
    return 1;
}

bool cstr_pop(c_string *s, len_t len)
{
    if (len == 0)
    {
        return true;
    }
    s->data[len - 1] = '\0';
    return false;
}

bool cstr_fill(c_string *a, size_t start, const c_string *b, len_t a_len, len_t b_len)
{
    if (a_len - start < b_len)
    {
        return true;
    }
    // strcpy(a + start, b);
    memcpy(a->data + start, b->data, b_len * sizeof(char));
    return false;
}

bool cstr_fill_unsafe(c_string *a, size_t start, const c_string *b, len_t b_len)
{
    memcpy(a->data + start, b->data, b_len * sizeof(char));
    return false;
}

bool cstr_fill_unsafe_capacity(c_string *a, size_t start, const c_string *b, len_t a_len, len_t b_len)
{
    size_t sz, capa;
    if (start + b_len > a_len)
    {
        sz = b_len + start;
        capa = sz + 1;
        if (capa > a->capa)
        {
            if (cstr_recapa(a, capa))
            {
                return true;
            }
            
        }
        memcpy(a->data + start, b->data, b_len * sizeof(char));
        a->data[sz] = '\0';
        return false;
    }
    sz = a_len;
    capa = sz + 1;
    memcpy(a->data + start, b->data, b_len * sizeof(char));
    return false;
}

bool cstr_reserve(c_string *s, size_t start, size_t length, len_t s_len)
{
    size_t s_len_2 = s_len + length + 1;
    if (s_len_2 > s->capa)
    {
        if (cstr_recapa(s, s_len_2))
        {
            return true;
        }
        
    }
    if (s_len - start < length)
    {
        memset(s->data + s_len, s->data[start], length + start - s_len);
    }
    memmove(s->data + start + length, s->data + start, s_len);
    s->data[s_len + length] = '\0';
    return false;
}

bool cstr_reserve_unsafe(c_string *s, size_t start, size_t length, len_t s_len)
{
    size_t s_len_2 = s_len + length + 1;
    if (s_len_2 > s->capa)
    {
        if (cstr_recapa(s, s_len_2))
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
    memmove(s->data + start + length, s->data + start, s_len);
    s->data[s_len + length] = '\0';
    return false;
}

bool cstr_reserve_set(c_string *s, size_t start, size_t length, int setch, len_t s_len)
{
    size_t s_len_2 = s_len + length + 1;
    if (s_len_2 > s->capa)
    {
        if (cstr_recapa(s, s_len_2))
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
    memmove(s->data + start + length, s->data + start, s_len);
    memset(s->data + start, setch, length);
    s->data[s_len + length] = '\0';
    return false;
}

bool cstr_reserve_cpy(c_string *s, size_t start, c_string *sub, len_t s_len, len_t sub_len)
{
    size_t s_len_2 = s_len + sub_len + 1;
    if (s_len_2 > s->capa)
    {
        if (cstr_recapa(s, s_len_2))
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
    memmove(s->data + start + sub_len, s->data + start, s_len);
    memcpy(s->data + start, sub->data, sub_len);
    s->data[s_len + sub_len] = '\0';
    return false;
}

bool cstr_insert(c_string *s, size_t start, c_string *sub, len_t s_len, len_t sub_len)
{
    size_t s_len_2 = s_len + sub_len + 1;
    if (s_len_2 > s->capa)
    {
        if (cstr_recapa(s, s_len_2))
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
    memmove(s->data + start + sub_len, s->data + start, s_len);
    memcpy(s->data + start, sub->data, sub_len);
    s->data[s_len + sub_len] = '\0';
    return false;
}

bool cstr_delete(c_string *s, size_t start, size_t length, len_t s_len)
{
    if (start >= s_len || start + length > s_len)
    {
        return true;
    }
    size_t startplength = start + length;
    for (size_t i = startplength; i < s_len; ++i)
    {
        s->data[i - length] = s->data[i];
    }
    s->data[s_len - length] = '\0';
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

bool cstr_pull(c_string *s, const char *c)
{
    size_t the_fewest_capa = strlen(c) + 1;
    if (s->capa < the_fewest_capa)
    {
        if (cstr_recapa(s, the_fewest_capa))
        {
            return true;
        }
        
    }
    strcpy(s->data, c);
    return false;
}

bool cstr_pull_set(c_string *s, size_t elements, int data_char)
{
    if (s->capa <= elements)
    {
        if (cstr_recapa(s, elements + 1))
        {
            return true;
        }
    }
    memset(s->data, data_char, elements);
    s->data[elements] = '\0';
    return false;
}

bool cstr_pull_chr(c_string *s, char c)
{
    if (s->capa < 2)
    {
        if (cstr_recapa(s, 2))
        {
            return true;
        }
    }
    s->data[0] = c;
    s->data[1] = '\0';
    return false;
}

c_string cstr_steal_len(char *ch, len_t size);

c_string cstr_steal(char *ch)
{
    return cstr_steal_len(ch, strlen(ch));
}

c_string cstr_steal_len(char *ch, len_t size)
{
    c_string res;
    res.capa = size + 1;
    res.data = ch;
    return res;
}

size_t cstr_find(c_string *s, c_string *sub, size_t start, len_t s_len, len_t sub_len)
{
#if 0
    "Sunday Algorithm"
#endif
    s->data += start;
    s_len -= start;
    if (sub_len == 0) return 0;
    if (s_len < sub_len) return -1;
    size_t shift_table[256];
    for (int i = 0; i < 256; ++i)
    {
        shift_table[i] = sub_len + 1;
    }
    int shcnt = 0;
    unsigned char uc;
    for (size_t i = sub_len - 1; i != (size_t)-1; --i)
    {
        uc = (unsigned char)sub->data[i];
        if (shift_table[uc] == sub_len + 1)
        {
            ++shcnt;
            shift_table[uc] = sub_len - i;
        }
        if (shcnt == 255)
        {
            break;
        }
        
    }
    /*unsigned char uc;
    for (size_t i = 0; i < sub_len; ++i)
    {
        uc = (unsigned char)sub->data[i];
        shift_table[uc] = sub_len - i;
    }*/
    
    size_t i = 0;
    while (i < s_len - sub_len)
    {
        size_t j = 0;
        while (j < sub_len && s->data[i + j] == sub->data[j])
        {
            ++j;
        }
        if (j == sub_len) return i;
        uc = (unsigned char)s->data[i + sub_len];
        i += shift_table[uc];
    }
    return -1;
}

size_t cstr_rfind_func(const c_string *s, const c_string *sub, size_t start, len_t s_len, len_t sub_len)
{
#if 0
    "Sunday Algorithm"
#endif
    sub_len = (start > sub_len) ? sub_len : start;
    if (sub_len == 0) return sub_len;
    if (s_len < sub_len) return -1;
    size_t shift_table[256];
    for (int i = 0; i < 256; ++i)
    {
        shift_table[i] = sub_len + 1;
    }
    int shcnt = 0;
    unsigned char uc;
    for (size_t i = sub_len - 1; i != (size_t)-1; --i)
    {
        uc = (unsigned char)sub->data[i];
        if (shift_table[uc] == sub_len + 1)
        {
            ++shcnt;
            shift_table[uc] = i + 1;
        }
        if (shcnt == 255)
        {
            break;
        }
        
    }
    /*unsigned char uc;
    for (size_t i = 0; i < sub_len; ++i)
    {
        uc = (unsigned char)sub->data[i];
        shift_table[uc] = sub_len - i;
    }*/
    size_t e = s_len - 1, se = sub_len - 1;
    size_t i = 0;
    while (i < s_len - sub_len)
    {
        size_t j = 0;
        while (j < sub_len && s->data[e - i - j] == sub->data[se - j])//
        {
            ++j;
        }
        if (j == sub_len) return s_len - i - j;
        uc = (unsigned char)s->data[e - i - sub_len];
        i += shift_table[uc];
    }
    return -1;
}

size_t cstr_rfind(const c_string *s, const c_string *sub, size_t start, len_t s_len, len_t sub_len)
{
    return cstr_rfind_func(s, sub, start + sub_len, s_len, sub_len);
}

size_t cstr_find_first_of(const c_string *s, char ch, len_t str_len)
{
    //size_t str_len = cstrlen(s);
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

size_t cstr_find_last_of(const c_string *s, char ch, len_t str_len)
{
    //size_t str_len = cstrlen(s);
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

void cstr_reverse(c_string *s, len_t s_len)
{
    for (size_t i = 0, j = s_len - 1; i < j; ++i, --j)
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
