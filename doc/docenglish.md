**c_string Library Documentation**

**Overview**

The `c_string` is a custom string processing library designed to provide additional string operation functionalities, built upon the standard library functions of C. It defines a structure named `c_string`, which encapsulates the capacity of the string and a pointer to the data. A series of functions are provided to manipulate this custom string type.

**Structure Definition**


```c
typedef struct c_string {  
    size_t capa;  // Capacity of the string  
    char *data;   // Pointer to the string data  
} c_string;
```
**Function List**

**init_cstr**

Initializes a `c_string` structure, allocates memory for it, and sets the initial value to an empty string.


```c
bool init_cstr(c_string *s);
```
**Parameters:**

* `s`: Pointer to the `c_string` structure

**Return Value:**

* `true` if memory allocation fails
* `false` if successful

**make_cstr**

Creates a new `c_string` based on the given C-style string.


```c
c_string make_cstr(const char *c);
```
**Parameters:**

* `c`: C-style string

**Return Value:**

* The newly created `c_string` structure

**cstrlen**

Returns the length of the `c_string` (similar to the `strlen` function).


```c
size_t cstrlen(const c_string *s);
```
**Parameters:**

* `s`: Pointer to the `c_string` structure

**Return Value:**

* Length of the `c_string`

**cstrcat**

Concatenates two `c_strings` together. If the capacity of the first `c_string` is insufficient to hold the concatenated string, it reallocates enough memory.


```c
bool cstrcat(c_string *a, const c_string *b);
```
**Parameters:**

* `a`: Pointer to the first `c_string`
* `b`: Pointer to the second `c_string`

**Return Value:**

* `true` if memory reallocation fails
* `false` if successful

**init_cstrcpy and cstrcpy**

Copies one `c_string` to another. `init_cstrcpy` checks if the source and destination are the same object before copying, while `cstrcpy` frees the memory of the destination object before performing the copy.


```c
c_string init_cstrcpy(c_string *a, const c_string *b);

c_string cstrcpy(c_string *a, const c_string *b);
```
**Parameters:**

* `a`: Pointer to the destination `c_string`
* `b`: Pointer to the source `c_string`

**Return Value:**

* The destination `c_string` with the copied content

**cstrcmp**

Compares the sizes of two `c_string`s (similar to the `strcmp` function).

```c
int cstrcmp(const c_string *a, const c_string *b);
```

**Parameters:**

* `a`, `b`: Pointers to the `c_string`s to be compared

**Return Value:**

* Negative if `a` is less than `b`
* Zero if `a` is equal to `b`
* Positive if `a` is greater than `b`

**cstrcspn**

Returns the position of the first occurrence of a given substring within a `c_string` (similar to the `strcspn` function).

```c
size_t cstrcspn(const c_string *a, const c_string *b);
```

**Parameters:**

* `a`: Pointer to the source `c_string`
* `b`: Pointer to the substring

**Return Value:**

* Position of the first occurrence of `b` in `a`

**cstrstr**

Searches for a given substring within a `c_string` and returns a pointer to the first occurrence.

```c
const char *cstrstr(const c_string *a, const c_string *b);
```

**Parameters:**

* `a`: Pointer to the source `c_string` in which to search for the substring.
* `b`: Pointer to the substring to search for.

**Return Value:**

* A pointer to the first occurrence of `b` in `a`, if found.
* `NULL` if the substring `b` is not found in `a`.

**cstr_substr**

Extracts a substring from a `c_string`.

```c
c_string cstr_substr(const c_string *s, size_t pos, size_t len);
```

**Parameters:**

* `s`: Pointer to the source `c_string` from which to extract the substring.
* `pos`: Starting position, indicating the index from which to start extracting the substring.
* `len`: Length of the substring.

**Return Value:**

* A new `c_string` containing the extracted substring from the source `c_string`.

**cstr_print**

Prints a `c_string` to the standard output (typically a terminal or console).

```c
void cstr_print(const c_string *s);
```

**Parameters:**

* `s`: Pointer to the `c_string` to be printed.

**Return Value:**

* None.

**Description:**

The `cstr_print` function prints the content of a `c_string` to the standard output device (typically a terminal or console). It uses `printf` or a similar function to perform the printing operation, ensuring that the null character ('\0') in the `c_string` is not interpreted as the end of the string.

This function is primarily used for debugging and logging purposes, allowing you to view the content of a `c_string` on the console. It does not return any value and does not modify the passed `c_string`.

<Title: Documentation for cstr_fprint, cstr_scan, cstr_fscan, cstr_fgets, cstr_pop, cstr_fill, and cstr_reserve Functions>

I. cstr_fprint

Function Prototype:


```c
int cstr_fprint(const char* format, const char* str, FILE* stream);
```
Function Description:

The cstr_fprint function is used to print a cstr string (const char* str) to a specified file stream (FILE* stream) according to a specified format (const char* format).

Parameters:

* `format`: Format string that can contain format specifiers, specifying how to print the cstr string.
* `str`: The cstr string to be printed.
* `stream`: The target file stream for writing the printed content.

Return Value:

* Returns a non-negative integer on successful printing, representing the number of characters printed successfully.
* Returns a negative value on failure.

II. cstr_scan

Function Prototype:


```c
const char* cstr_scan(const char* str, const char* format);
```
Function Description:

The cstr_scan function searches for a part in the cstr string (const char* str) that matches the specified format (const char* format) and returns the starting position of the matching part.

Parameters:

* `str`: The cstr string to be searched.
* `format`: The format string to be searched, which can contain format specifiers.

Return Value:

* If a matching part is found, it returns a pointer to the starting position of the matching part.
* If no matching part is found, it returns NULL.

III. cstr_fscan

Function Prototype:


```c
int cstr_fscan(const char* format, FILE* stream, cstr_t* str);
```
Function Description:

The cstr_fscan function reads a string from a specified file stream (FILE* stream) according to a specified format (const char* format) and stores it in a cstr_t* str.

Parameters:

* `format`: Format string specifying how to read the string from the file stream.
* `stream`: The source file stream for reading the string.
* `str`: A pointer to a cstr_t type for storing the read string.

Return Value:

* Returns a non-negative integer on successful reading, representing the number of characters read successfully.
* Returns a negative value on failure or when reaching the end of the file.

IV. cstr_fgets

Function Prototype:


```c
int cstr_fgets(cstr_t* str, int size, FILE* stream);
```
Function Description:

The cstr_fgets function reads a line of string from a specified file stream (FILE* stream) and stores it in a cstr_t* str.

Parameters:

* `str`: A pointer to a cstr_t type for storing the read string.
* `size`: The maximum number of characters (including the null character) that str can accommodate.
* `stream`: The source file stream for reading the string.

Return Value:

* Returns a non-negative integer on successful reading, representing the number of characters read successfully (excluding the null character).
* Returns a negative value on failure or when reaching the end of the file.

V. cstr_pop

Function Prototype:


```c
void cstr_pop(cstr_t* str);
```
Function Description:

The cstr_pop function is used to remove the last character from a cstr_t* str.

Parameters:

* `str`: A pointer to a cstr_t type from which the last character will be removed.

Return Value:

* No return value.

VI. cstr_fill

Function Prototype:


```c
void cstr_fill(cstr_t* str, int size, char c);
```
Function Description:

The cstr_fill function fills the first size characters of a cstr_t* str with a specified character c.

Parameters:

* `str`: A pointer to a cstr_t type to be filled.
* `size`: The number of characters to be filled.
* `c`: The character to be used for filling.

Return Value:

* No return value.

```c
cstr_reserve
```

Prototype: bool cstr_reserve(c_string*s, size_t start, size_t length)
Description: Adjusts the size of the c_string s to have uninitialized space of the specified length after the position start. If memory reallocation fails, true is returned indicating failure. Otherwise, the existing content is moved from the start position to accommodate the new space.
Parameters:
*s: A pointer to the c_string object.
*start: The position after which to add the uninitialized space.
*length: The size of the uninitialized space to add.
*Return Value: true if memory reallocation fails, false otherwise.

<cstr_reserve_cpy, cstr_delete, cstr_free, cstr_free_high Function Documentation>

**Function Name**: `cstr_reserve_cpy`

**Description**:
This function is used to copy the content of one `c_string` to a specified position in another `c_string`, and reallocates memory if necessary to accommodate the new content.

**Parameters**:

* `s`: Pointer to the destination `c_string` where the copied content will be stored.
* `start`: `size_t` type indicating the position in the destination `c_string` where the new content should be inserted.
* `a`: Pointer to the source `c_string` containing the content to be copied.

**Return Value**:

* Returns `true` if memory reallocation fails.
* Returns `false` if the operation is successful.

**Function Name**: `cstr_delete`

**Description**:
This function is used to delete a specified range of characters from a `c_string`.

**Parameters**:

* `s`: Pointer to the `c_string` from which content will be deleted.
* `start`: `size_t` type indicating the starting position of the content to be deleted.
* `length`: `size_t` type indicating the length of the content to be deleted.

**Return Value**:

* Returns `true` if the given position or length is invalid.
* Returns `false` if the operation is successful.

**Function Name**: `cstr_free`

**Description**:
This function is used to release the memory allocated for a `c_string`.

**Parameters**:

* `s`: Pointer to the `c_string` whose memory is to be released.

**Return Value**:
None.

**Function Name**: `cstr_free_high`

**Description**:
This function is used to release the memory allocated for multiple `c_strings`.

**Parameters**:

* `size`: `size_t` type indicating the number of `c_strings` to be released.
* `...`: Variable argument list containing pointers to the `c_strings` to be released.

**Return Value**:
None.

**Notes**:

* The `cstr_reserve_cpy` function may reallocate memory for the destination `c_string` if necessary. Therefore, ensure that the pointer to the destination `c_string` is valid and there is enough memory available for allocation.
* After deleting content using the `cstr_delete` function, the remaining content is shifted to the left to fill the gap, and a null character (`\0`) is added at the end.
* The `cstr_free` function only releases the memory allocated for the data part of the `c_string` and does not release the memory for the `c_string` structure itself.
* The `cstr_free_high` function uses a variable argument list to receive pointers to multiple `c_strings`. Therefore, when calling this function, provide the correct number of pointers and ensure that each pointer is valid.