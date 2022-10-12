// Filename: dynamic_string.c
// IFJ 2022/2023 project
// TRP variant
//
// Interface for working with dynamic strings
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "dynamic_string.h"

// Clears dynamic string
int d_string_clear(DString_t *d_string) {
    if (d_string == NULL) {
        return INTERNAL_ERR;
    }
    d_string->length = 0;
    d_string->str[d_string->length] = '\0';

    return OK;
}

// Initializes dynamic string
int d_string_init(DString_t *d_string) {
    if (d_string == NULL) {
        return INTERNAL_ERR;
    }
    d_string->str = (char *)malloc(DYNAMIC_STRING_INIT_SIZE);
    if (d_string->str == NULL) {
        return INTERNAL_ERR;
    }
    if (d_string_clear(d_string) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    d_string->allocated_size = DYNAMIC_STRING_INIT_SIZE;
    return OK;
}

// Frees and clears dynamic string
int d_string_free_and_clear(DString_t *d_string) {
    if (d_string == NULL) {
        return INTERNAL_ERR;
    }
    d_string_clear(d_string);
    free(d_string->str);
    return OK;
}

// Adds character to dynamic string
int d_string_add_char(DString_t *d_string, char c) {
    if (d_string == NULL) {
        return INTERNAL_ERR;
    }
    if (d_string->length + 1 >= d_string->allocated_size) {
        d_string->allocated_size += DYNAMIC_STRING_INIT_SIZE;
        d_string->str =
            (char *)realloc(d_string->str, d_string->allocated_size);
        if (d_string->str == NULL) {
            return INTERNAL_ERR;
        }
    }
    d_string->str[d_string->length++] = c;
    d_string->str[d_string->length] = '\0';
    return OK;
}

// Appends dynamic string by another constant string
int d_string_add_str(DString_t *d_string, const char *c_str) {
    if (d_string == NULL || c_str == NULL) {
        return INTERNAL_ERR;
    }
    unsigned int c_str_len = strlen(c_str);
    if (d_string->length + c_str_len >= d_string->allocated_size) {
        d_string->allocated_size += c_str_len + DYNAMIC_STRING_INIT_SIZE;
        d_string->str = (char *)realloc(
            d_string->str, d_string->allocated_size * sizeof(char));
        if (d_string->str == NULL) {
            return INTERNAL_ERR;
        }
    }
    d_string->length += c_str_len;
    strcat(d_string->str, c_str);
    d_string->str[d_string->length] = '\0';
    return OK;
}

// Appends dynamic string by another dynamic string
int d_string_add_d_string(DString_t *d_string, DString_t *d_string_to_add) {
    printf("d_string_add_d_string");
    printf("d_string_to_add->str: %s", d_string_to_add->str);
    printf("d_string->str: %s", d_string->str);
    return NOT_IMPLEMENTED;
}

// Compares dynamic string with constant string
int d_string_cmp(DString_t *d_string, const char *c_str) {
    if (d_string == NULL || c_str == NULL) {
        return INTERNAL_ERR;
    }
    return strcmp(d_string->str, c_str);
}

// Copies dynamic string to another dynamic string
int d_string_copy(DString_t *src, DString_t *dest) {
    if (src == NULL || dest == NULL) {
        return INTERNAL_ERR;
    }
    if (d_string_clear(dest) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    if (d_string_add_str(dest, src->str) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    return OK;
}
