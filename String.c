/// String.c
///
/// ADT for Strings
///
/// @author Ryan Ferrer rvf6846

#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "String.h"

/// Struct to store string data
struct string_s {
    size_t capacity;
    size_t length;
    unsigned char* data;
};

/// Create a String entity
String str_create(size_t capacity, size_t length, const unsigned char* data){
    
    String str = malloc(sizeof(struct string_s));
    assert(str != NULL);

    if(capacity == 0){
        str->capacity = 0;
        str->length = 0;
        str->data = NULL;
        return str;
    }

    size_t cap = (capacity >= length) ? capacity : length;
    str->capacity = cap;

    str->data = malloc(cap * sizeof(unsigned char));
    assert(str->data != NULL);

    if (length > 0 && data != NULL) {
        for (size_t i = 0; i < length; i++) {
            str->data[i] = data[i];
        }
        str->length = length;
    } else {
        str->length = 0;
    }

    return str;
}

/// Deallocate supplied string
void str_destroy(String str){
    
    assert(str != NULL);

    free(str->data);
    free(str);
}

/// Create a C-string from String
char* str_to_c(const String str){

    assert(str != NULL);

    char* c_str = malloc(str->length * sizeof(unsigned char) + 1);
    assert(c_str != NULL);

    for(size_t i = 0; i < str->length; ++i){
        c_str[i] = str->data[i];
    }
    c_str[str->length] = '\0';

    return c_str;
}

size_t str_length(const String str){
    
    assert(str != NULL);
    
    return str->length;
}

/// Reverse the input String
String str_reverse(const String str){
    
    assert(str != NULL);
    
    String rev = str_create(str->capacity, str->length, str->data);

    for(size_t i = 0; i < rev->length/2; ++i){
        unsigned char tmp = rev->data[i];
        rev->data[i] = rev->data[rev->length - i - 1];
        rev->data[rev->length - i - 1] = tmp;
    }

    return rev;
}

/// Copy a string to another string
size_t str_copy(String dst, const String src){

    assert(src != NULL);
    assert(dst != NULL);

    if(dst->capacity < src->length){
        unsigned char* tmp = realloc(dst->data, src->length);
        assert(tmp != NULL);
        dst->data = tmp;
        dst->capacity = src->length;
    }
    dst->length = src->length;

    for(size_t i = 0; i < dst->length; ++i){
        dst->data[i] = src->data[i];
    }

    return dst->length;
}

/// Concatonate two strings
size_t str_concat(String dst, const String src){

    assert(dst != NULL);
    assert(src != NULL);

    if(dst->capacity < dst->length + src->length){
        unsigned char* tmp = realloc(dst->data, dst->length + src->length);
        assert(tmp != NULL);
        dst->data = tmp;
        dst->capacity = dst->length + src->length;
    }

    size_t old_length = dst->length;
    dst->length += src->length;
    
    for(size_t i = 0; i < src->length; ++i){
        dst->data[i + old_length] = src->data[i];
    }

    return dst->length;
}

/// Compare two strings
int str_compare(const String str1, const String str2) {

    assert(str1 != NULL);
    assert(str2 != NULL);

    size_t min_len = str1->length < str2->length ? str1->length : str2->length;

    for (size_t i = 0; i < min_len; ++i) {
        if (str1->data[i] != str2->data[i])
            return (int)(str1->data[i] - str2->data[i]);
    }

    return (int)(str1->length - str2->length);
}

/// Get a character from an index
int str_char_at(const String str, int index){
    
    assert(str != NULL);

    if(index <= (int) -str->length || index >= (int) str->length) return STR_ERROR;

    if(index < 0) index += str->length;

    return str->data[index];
}

/// Get a substring
String str_substring(const String str, int start, int end){
    
    assert(str != NULL);

    if (start < 0) start += str->length;
    if (end < 0) end += str->length;

    if (start < 0 || end < 0 || start >= (int) str->length || end >= (int) str->length || start > end)
        return NULL;

    size_t len = end - start + 1;
    String substr = str_create(len, 0, NULL);

    for(size_t i = 0; i < len; i++){
        substr->data[i] = str->data[start + i];
    }
    substr->length = len;

    return substr;
}
