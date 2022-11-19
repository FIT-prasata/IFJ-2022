#pragma once

// Filename: scanner.h
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// EXTERNAL INCLUDES
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>

#include "ctype.h"

// LOCAL INCLUDES
#include "dynamic_string.h"
#include "error.h"

// Token types
typedef enum T_type {
    // OPERATORS, ordered from highest precedence to lowest
    T_LT,  // <
    T_GT,  // >
    T_LE,  // <=
    T_GE,  // >=
    T_EQ,  // ===
    T_NE,  // !==

    // KEYWORDS
    K_ELSE,   // else
    K_FLOAT,  // float
    K_FUNC,   // function
    K_IF,     // if
    K_INT,    // int
    K_NULL,   // null
    K_RET,    // return
    K_STR,    // string
    K_VOID,   // void
    K_WHILE,  // while

    // PUNCTUATORS
    T_LCBR,    // {
    T_RCBR,    // }
    T_LBR,     // (
    T_RBR,     // )
    T_SEMCOL,  // ;
    T_COL,     // :
    T_CONCAT,  // .

    // EXPRESSIONS
    T_MUL,     // *
    T_DIV,     // /
    T_ADD,     // +
    T_SUB,     // -
    T_ASSIGN,  // =
    T_NEG,     // !

    // TYPES
    T_INT,     // integer type
    T_FLOAT,   // float type
    T_STRING,  // string type

    // OTHERS
    T_ID,       // variable identifier
    T_FUNC_ID,  // function identifier
    T_EOF,      // end of file
    T_EOL,      // end of line
    T_UNDEF,    // undefined type
    T_SEM,      // semicolon
    T_KEYWORD

} T_type_t;

// Token attribute
typedef union {
    char *string;
    int value;
    double dec_value;
} T_attr_t;

// Token struct
typedef struct {
    T_type_t type;       // type of token, one of T_type constants
    T_attr_t attribute;  // attribute of token
} Token_t;

// Gets first non-space character from input file
char get_non_white(void);

// Sets token type
// @param token - token to be set
// @param type - type to be set
void set_type(Token_t *token, T_type_t type);

// TODO: Why does lc returns char in bc int?
// Skips line comment
char skip_lc(void);

// Skips block comment
int skip_bc(void);

// Sets token value to either specific keyword or function name
// @param token - token to be set
// @param *curr - pointer to current character
int keyword_handler(Token_t *token, char *curr);

// Sets token value to number
// @param token - token to be set
// @param *curr - pointer to current character
int num_handler(Token_t *token, char *curr);

// Sets token value to string
// @param token - token to be set
int string_handler(Token_t *token);

// TODO
int id_handler(Token_t *token);

// TODO
int scan(Token_t *token);