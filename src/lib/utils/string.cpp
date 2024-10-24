#include <stddef.h>
#include "include/kernel/memory.h"

// String structure
typedef struct {
    char* data;
    size_t length;
} String;

// Initialize an empty string
void string_init(String* str) {
    str->data = NULL;
    str->length = 0;
}

// Create a string from a C-style string
void string_create(String* str, const char* cstr) {
    str->length = 0;
    while (cstr[str->length] != '\0') str->length++;
    str->data = (char*)m_alloc(str->length + 1);
    for (size_t i = 0; i <= str->length; i++) str->data[i] = cstr[i];
}

void string_free(String* str) {
    m_free((int)str->data);
    str->data = NULL;
    str->length = 0;
}

size_t string_length(const String* str) {
    return str->length;
}

int string_empty(const String* str) {
    return str->length == 0;
}

char string_char_at(const String* str, size_t index) {
    if (index < str->length) return str->data[index];
    return '\0';
}

void string_copy(String* dest, const String* src) {
    string_free(dest);
    dest->length = src->length;
    dest->data = (char*)m_alloc(dest->length + 1);
    for (size_t i = 0; i <= dest->length; i++) dest->data[i] = src->data[i];
}

void string_concat(String* dest, const String* src) {
    size_t new_length = dest->length + src->length;
            char* new_data = (char*)m_alloc(new_length + 1);
    for (size_t i = 0; i < dest->length; i++) new_data[i] = dest->data[i];
    for (size_t i = 0; i <= src->length; i++) new_data[dest->length + i] = src->data[i];
    m_free((int)dest->data);
    dest->data = new_data;
    dest->length = new_length;
}

int string_compare(const String* str1, const String* str2) {
    size_t min_length = str1->length < str2->length ? str1->length : str2->length;
    for (size_t i = 0; i < min_length; i++) {
        if (str1->data[i] < str2->data[i]) return -1;
        if (str1->data[i] > str2->data[i]) return 1;
    }
    if (str1->length < str2->length) return -1;
    if (str1->length > str2->length) return 1;
    return 0;
}

void string_substring(String* dest, const String* src, size_t start, size_t length) {
    if (start >= src->length) {
        string_init(dest);
        return;
    }
    if (start + length > src->length) length = src->length - start;
    dest->length = length;
    dest->data = (char*)m_alloc(length + 1);
    for (size_t i = 0; i < length; i++) dest->data[i] = src->data[start + i];
    dest->data[length] = '\0';
}

size_t string_find(const String* haystack, const String* needle, size_t start) {
    if (start >= haystack->length) return (size_t)-1;
    for (size_t i = start; i <= haystack->length - needle->length; i++) {
        size_t j;
        for (j = 0; j < needle->length; j++) {
            if (haystack->data[i + j] != needle->data[j]) break;
        }
        if (j == needle->length) return i;
    }
    return (size_t)-1;
}

void string_replace(String* str, size_t start, size_t length, const String* replacement) {
    if (start >= str->length) return;
    if (start + length > str->length) length = str->length - start;
    size_t new_length = str->length - length + replacement->length;
    char* new_data = (char*)m_alloc(new_length + 1);
    for (size_t i = 0; i < start; i++) new_data[i] = str->data[i];
    for (size_t i = 0; i < replacement->length; i++) new_data[start + i] = replacement->data[i];
    for (size_t i = start + length; i <= str->length; i++) new_data[i - length + replacement->length] = str->data[i];
    m_free((int)str->data);
    str->data = new_data;
    str->length = new_length;
}

void string_from_int(String* str, int value) {
    char buffer[20];
    int i = 0;
    int is_negative = value < 0;
    if (is_negative) value = -value;
    do {
        buffer[i++] = value % 10 + '0';
        value /= 10;
    } while (value);
    if (is_negative) buffer[i++] = '-';
    str->length = i;
    str->data = (char*)m_alloc(i + 1);
    for (int j = 0; j < i; j++) str->data[j] = buffer[i - 1 - j];
    str->data[i] = '\0';
}


