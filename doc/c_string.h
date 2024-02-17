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

bool init_cstr(c_string *s)
{
    s->capa = 1;
    s->data = (char *)malloc(sizeof(char));
    if (s->data == NULL)
    {
        return true;
    }
    s->data[0] = '\0';
    return false;
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

size_t cstrlen(const c_string *s)
{
    return strlen(s->data);
}

/*void cstrcat(c_string *a, c_string *b)
{
    size_t sz1 = cstrlen(a), sz2 = cstrlen(b);
    a->capa = sz1 + sz2 + 1ull;
    a->data = (char *)realloc(a->data, sizeof(char) * a->capa);
    if (a->data == NULL)
    {
        //fprintf(stderr, "Memory reallocation failed!\n");
        return;
    }
    for (size_t i = 0; i < sz2; ++i)
    {
        a->data[sz1 + i] = b->data[i];
    }
    a->data[sz1 + sz2] = '\0';
}*/

bool cstrcat(c_string *a, const c_string *b)
{
    size_t sz1 = cstrlen(a), sz2 = cstrlen(b);
    size_t fewest_capa = sz1 + sz2 + 1ull;
    if (a->capa < fewest_capa)
    {
        char *new_data = (char *)realloc(a->data, sizeof(char) * fewest_capa);
        if (new_data == NULL)
        {
            //fprintf(stderr, "Memory reallocation failed!\n");
            return 1;
        }
        a->capa = fewest_capa;
        a->data = new_data;
    }
    strcat(a->data, b->data);
    return 0;
}

/*bool cstrcat(c_string *a, const c_string *b)
{
    size_t sz1 = cstrlen(a);
    size_t sz2 = cstrlen(b);
    size_t new_capa = sz1 + sz2 + 1;
    if (a->capa < new_capa)
    {
        char *new_data = (char *)realloc(a->data, new_capa);
        if (new_data == NULL)
        {
            free(a->data);
            a->data = NULL;
            a->capa = 0;
            return true;
        }
        a->data = new_data;
        a->capa = new_capa;
    }
    strcat(a->data, b->data);
    return false;
}*/

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

size_t cstrcspn(const c_string *a, const c_string *b)
{
    return strcspn(a->data, b->data);
}

char *cstrstr(const c_string *a, const c_string *b)
{
    return strstr(a->data, b->data);
}

c_string cstr_substr(const c_string *s, size_t start, size_t length)
{
    c_string res;
    res.capa = length + 1;
    res.data = (char *)malloc( res.capa * sizeof(char) );
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
            s->data = (char *)realloc(s->data, s->capa * sizeof(char));
            if (s->data == NULL)
            {
                // fprintf(stderr, "Memory reallocation failed!\n");
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
            s->data = (char *)realloc(s->data, s->capa * sizeof(char));
            if (s->data == NULL)
            {
                // fprintf(stderr, "Memory reallocation failed!\n");
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
            s->data = (char *)realloc(s->data, s->capa * sizeof(char));
            if (s->data == NULL)
            {
                // fprintf(stderr, "Memory reallocation failed!\n");
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
    //strcpy(a + start, b);
    memcpy(a->data + start, b->data, sz2 * sizeof(char) );
    return false;
}

bool cstr_reserve(c_string *s, size_t start, size_t length)
{
    size_t sz = cstrlen(s), sz2 = sz + length + 1;
    if (sz2 > s->capa)
    {
        char *new_data = (char *)realloc(s->data, sz2 * sizeof(char) );
        if (new_data == NULL)
        {
            return true;
        }
        s->capa = sz2;
        s->data = new_data;
    }
    if (sz - start < length)
    {
        memset(s->data + sz, s->data[start], length + start - sz);
    }
    size_t sz_start = sz - start;
    for (size_t i = 0; i < sz_start; ++i)
    {
        s->data[sz - i - 1 + length] = s->data[sz - i - 1];
    }
    s->data[sz + length] = '\0';
    return false;
}

bool cstr_reserve_set(c_string *s, size_t start, size_t length, int val)
{
    if (val == 0)
    {
        return true;
    }
    size_t sz = cstrlen(s), sz2 = sz + length + 1;
    if (sz2 > s->capa)
    {
        char *new_data = (char *)realloc(s->data, sz2 * sizeof(char) );
        if (new_data == NULL)
        {
            return true;
        }
        s->capa = sz2;
        s->data = new_data;
    }
    size_t sz_start = sz - start;
    for (size_t i = 0; i < sz_start; ++i)
    {
        s->data[sz - i - 1 + length] = s->data[sz - i - 1];
    }
    s->data[sz + length] = '\0';
    memset(s->data + start, val, length);
    return false;
}

bool cstr_reserve_cpy(c_string *s, size_t start, const c_string *a)
{
    size_t length = cstrlen(a), sz = cstrlen(s), sz2 = sz + length + 1;
    if (sz2 > s->capa)
    {
        char *new_data = (char *)realloc(s->data, sz2 * sizeof(char) );
        if (new_data == NULL)
        {
            return true;
        }
        s->capa = sz2;
        s->data = new_data;
    }
    size_t sz_start = sz - start;
    for (size_t i = 0; i < sz_start; ++i)
    {
        s->data[sz - i - 1 + length] = s->data[sz - i - 1];
    }
    s->data[sz + length] = '\0';
    memcpy(s->data + start, a->data, length);
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
        free(va_arg(valist, c_string *)->data);
    }
    va_end(valist);
}

#endif
