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
    K_ELSE,  // else
    K_FLOAT, // float
    K_FUNC,  // function
    K_IF,    // if
    K_INT,   // int
    K_NULL,  // null
    K_RET,   // return
    K_STR,   // string
    K_VOID,  // void
    K_WHILE, // while

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

    // TYPES
    T_INT,    // integer type
    T_FLOAT,  // float type
    T_STRING, // string type

    // OTHERS
    T_ID,      // variable identifier
    T_FUNC_ID, // function identifier
    T_EOF,     // end of file
    T_EOL,     // end of line
    T_UNDEF,   // undefined type
    T_SEM      // semicolon

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
    S_FUNC_ID,
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
    T_type_t type;      // type of token, one of T_type constants
    T_attr_t attribute; // attribute of token
} Token_t;

int is_keyword(Token_t *token, char *curr);
int num_handler(Token_t *token, char *curr);
int string_handler(Token_t *token);
int id_handler(Token_t *token);
int scan(Token_t *token);