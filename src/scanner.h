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
    T_UNDEF,     // undefined type
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
    K_FLOAT_NULL,
    K_FUNC,   // function
    K_IF,     // if
    K_INT,    // int
    K_INT_NULL,
    K_NULL,   // null
    K_RET,    // return
    K_STR,    // string
    K_STR_NULL,
    K_VOID,   // void
    K_WHILE,  // while

    // PUNCTUATORS
    T_LCBR,    // {
    T_RCBR,    // }
    T_LBR,     // (
    T_RBR,     // )
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
    T_ID,        // variable identifier
    T_FUNC_ID,   // function identifier
    T_EOF,       // end of file
    T_EOL,       // end of line
    T_SEM,       // semicolon
    T_PROLOG1,   // prolog <?php
    T_PROLOG2,   // prolog declare(strict_types=1);
    T_END_PROLOG // end of prolog

} T_type_t;

// FSM states
typedef enum T_State{
    // OPERATOR STATES
    S_LT,  // <
    S_GT,  // >
    S_LE,  // <=
    S_GE,  // >=
    S_POSS_EQ,  // ==
    S_EQ, // ===
    S_POSS_NEQ, // !=
    S_NEQ, // !==

    // PUNCTUATOR STATES
    S_LCBR,    // {
    S_RCBR,    // }
    S_LBR,     // (
    S_RBR,     // )
    S_SEM,  // ;
    S_COL,     // :
    S_CONCAT,  // .

    // EXPRESSION STATES
    S_MUL,     // *
    S_DIV,     // /
    S_ADD,     // +
    S_SUB,     // -
    S_ASSIGN,  // =
    S_NEG,     // !

    // COMMENT STATES
    S_BC, // /*
    S_POSS_BC_END,   // *
    S_BC_END, // */
    S_LC, // //

    // CONSTANT STATES
    S_INT, // integer constant
    S_INT_END,
    S_FLOAT, // float constant
    S_FLOAT_END,
    S_STRING, // string constant
    S_STRING_END,
    S_STRING_ESC,

    // OTHER STATES
    S_SPACE,
    S_ID1,
    S_ID2,
    S_EOF,
    S_START,
    S_ERR,
    S_KEYWORD,
    S_KEYWORD_END,
    QUEST_MARK,
    // S_PROL_ST1,
    // S_PROL_ST2,
    S_PROL_END,
    // S_PROL_SKIP

} T_State_t;

// Token attribute - commented for testing purposes!!!
// typedef union {
//     char *string;
//     int value;
//     double dec_value;
// } T_attr_t;

typedef struct { // only for testing purposes!!! change afterwards
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
int skip_bc(int *line_num);

// TODO
//int keyword_handler(DString_t *dString, Token_t *token);

// Sets token value to number
// @param token - token to be set
// @param *curr - pointer to current character
int num_handler(Token_t *token, char *curr);

// Sets token value to string
// @param token - token to be set
//int string_handler(Token_t *token);

// TODO
int id_handler(Token_t *token);

// TODO
int scan(Token_t *token);

// TODO
int prolog_handler();