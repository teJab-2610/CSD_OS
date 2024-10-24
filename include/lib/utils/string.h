#ifndef STRING_H
#define STRING_H

#include <stddef.h>

// String structure
typedef struct {
    char* data;
    size_t length;
} String;

// Function prototypes
void string_init(String* str);
void string_create(String* str, const char* cstr);
void string_free(String* str);
size_t string_length(const String* str);
int string_empty(const String* str);
char string_char_at(const String* str, size_t index);
void string_copy(String* dest, const String* src);
void string_concat(String* dest, const String* src);
int string_compare(const String* str1, const String* str2);
void string_substring(String* dest, const String* src, size_t start, size_t length);
size_t string_find(const String* haystack, const String* needle, size_t start);
void string_replace(String* str, size_t start, size_t length, const String* replacement);
void string_from_int(String* str, int value);

#endif // STRING_H
