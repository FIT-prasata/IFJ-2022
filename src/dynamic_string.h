#pragma once

// Filename: dynamic_string.h
// IFJ 2022/2023 project
// TRP variant
//
// Interface for working with dynamic strings - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

#include "error.h"
#include "string.h"

#define DYNAMIC_STRING_INIT_SIZE 8

typedef struct DynamicString {
    char *str;
    unsigned int length;
    unsigned int allocated_size;
} DString_t;

// Clears dynamic string
// @param d_string - pointer to dynamic string
// @return - status code
int d_string_clear(DString_t *d_string);

// Initializes dynamic string
// @param d_string - pointer to dynamic string
// @return - status code
int d_string_init(DString_t *d_string);

// Frees dynamic string
// @param d_string - pointer to dynamic string
// @return - status code
int d_string_free_and_clear(DString_t *d_string);

// Adds character to dynamic string
// @param d_string - pointer to dynamic string
// @param c - character to be added
// @return - status code
int d_string_add_char(DString_t *d_string, char c);

// Appends dynamic string by another constant string
// @param d_string - pointer to dynamic string
// @param c_str - string to be added
// @return - status code
int d_string_add_str(DString_t *d_string, const char *c_str);

// TODO: mby not possible or even necessary to implement
// Appends dynamic string by another dynamic string
// @param d_string - pointer to dynamic string
// @param str - string to be added
// @return - status code
int d_string_add_d_str(DString_t *d_string, const DString_t *d_str);

// Compares dynamic string with constant string
// @param d_string - pointer to dynamic string
// @param c_str - string to be compared with
// @return - status code
int d_string_cmp(DString_t *d_string, const char *c_str);

// Copies dynamic string to another dynamic string
// @param src - pointer to source dynamic string
// @param dest - pointer to dynamic string to be copied to
// @return - status code
int d_string_copy(DString_t *src, DString_t *dest);