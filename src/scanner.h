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
#include <stdio.h>
#include <stdbool.h>

// LOCAL INCLUDES
#include "error.h"

// Token types
typedef enum {
    // OPERATORS, ordered from highest precedence to lowest
    T_LT,   // <
    T_GT,   // >
    T_LE,   // <=
    T_GE,   // >=
    T_EQ,   // ===
    T_NE,   // !==

    // KEYWORDS
    T_ELSE,  // else
    T_FLOAT, // float
    T_FUNC,  // function
    T_IF,    // if
    T_INT,   // int
    T_NULL,  // null
    T_RET,   // return
    T_STR,   // string
    T_VOID,  // void
    T_WHILE, // while

    // PUNCTUATORS
    T_LCBR,   // {
    T_RCBR,   // }
    T_LBR,    // (
    T_RBR,    // )
    T_SEMCOL, // ;
    T_COL,    // :
    T_CONCAT, // .

    // EXPRESSIONS
    T_MUL,    // *
    T_DIV,    // /
    T_ADD,    // +
    T_SUB,    // -
    T_ASSIGN, // =
    T_NEG,    // !

    // OTHERS
    T_ID,   // identifier
    T_EOF,  // end of file
    T_EOL,  // end of line
    T_UNDEF // undefined type

} T_type_t;

// FSM states
typedef enum {
    // OPERATORS STATES
    S_LT,
    S_GT,
    S_LE,
    S_GE,
    S_POSS_EQ,
    S_EQ,
    S_POSS_NE,
    S_NE,

    // PUNCTUATORS STATES
    S_LCBR,
    S_RCBR,
    S_LBR,
    S_RBR,
    S_SEMCOL,
    S_COL,
    S_CONCAT,

    // EXPRESSIONS STATES
    S_MUL,
    S_DIV,
    S_ADD,
    S_SUB,
    S_ASSIGN,
    S_NEG,

    // COMMENTS STATES
    S_BC_START,
    S_POSS_BC_END,
    S_BC_END,
    S_LC,

    // CONSTANTS STATES
    S_ZERO,
    S_INT,
    S_FLOAT,
    S_POSS_EXP,
    S_EXP_SIGN,
    S_EXP,
    S_STR_START,
    S_STR_ESC,
    S_STR_OCT1,
    S_STR_OCT2,
    S_STR_HEX1,
    S_STR_HEX2,
    S_STR_SPEC,
    S_STR_END,

    // OTHER STATES
    S_SPACE,
    S_ID1,
    S_ID2,
    S_EOF,
    S_START,
    S_ERR

} State_t;

// Token attribute
typedef union {
    char *string;
    int value;
    double dec_value;
} T_attr_t;


// Token struct
typedef struct {
    T_type_t type; // type of token, one of T_type constants
    T_attr_t attribute; // attribute of token
} Token_t;

// Defines

// get next token from file pointer
Token_t get_token(FILE *file_ptr);


bool matches_keyword(Token_t token);

bool scan(Token_t token, FILE *stream);