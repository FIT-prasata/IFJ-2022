#pragma once

#ifndef _SCANNER_H_
#define _SCANNER_H_

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


// LOCAL INCLUDES
#include "dynamic_string.h"
#include "error.h"

// line counting
extern int line_num;

// Token types
typedef enum T_type {
    T_UNDEF,     // undefined type
    // OPERATORS, ordered from highest precedence to lowest
    T_LT,  // <
    T_GT,  // >
    T_LEQ,  // <=
    T_GEQ,  // >=
    T_EQ,  // ===
    T_NEQ,  // !==

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
    T_COMMA,   // ,

    // EXPRESSIONS
    T_MUL,     // *
    T_DIV,     // /
    T_ADD,     // +
    T_SUB,     // -
    T_ASSIGN,  // =

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
    S_POSS_EQ,  // ==
    S_EQ_OK, // ===
    S_NEQ_OK, // !==
    S_POSS_NEQ, // !=
    S_NEQ, // !

    // PUNCTUATOR STATES
    S_LCBR,    // {
    S_RCBR,    // }
    S_LBR,     // (
    S_RBR,     // )
    S_SEM,  // ;
    S_COL,     // :
    S_CONCAT,  // .
    S_COMMA,  // ,

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
    S_ID,
    S_ID_END,
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

// Token attribute
typedef struct {
    char *string;
    int value;
    double dec_value;
} T_attr_t;

// Token struct
typedef struct {
    T_type_t type;       // type of token, one of T_type constants
    T_attr_t attribute;  // attribute of token
} Token_t;


/**
 * @brief Checks if character is a white character (not a newline)
 * 
 * @param input - current character
 * @return  1 if character is a white character, 0 otherwise
 */
int is_white(int input);


/**
 * @brief Function for handling prolog
 * 
 * @return 0 if prolog is correct, 1 otherwise 
 */
int prolog_handler(void);


/**
 * @brief Function for handling epilog
 * 
 * @return 0 if epilog is correct, 1 otherwise  
 */
int epilog_handler(void);


/**
 * @brief Function for keyword handling
 * 
 * @param dString - pointer to dynamic strung
 * @param token - pointer to token
 * @return LEX_ERR if lexical error occurs
 * @return INTERNAL_ERR if memory problem occurs
 * @return OK if keyword is correct 
 */
int keyword_handler(DString_t *dString, Token_t *token);


/**
 * @brief Function for string handling
 * 
 * @param dString - pointer to dynamic strung
 * @param token - pointer to token
 * @return LEX_ERR if lexical error occurs
 * @return INTERNAL_ERR if memory problem occurs
 * @return OK if string is correct 
 */
int string_handler(DString_t *dString, Token_t *token);


/**
 * @brief Function for variable IDs handling
 * 
 * @param dString - pointer to dynamic strung
 * @param token - pointer to token
 * @return INTERNAL_ERR if memory problem occurs
 * @return OK if variable ID is correct 
 */
int id_handler(DString_t *dString, Token_t *token);


/**
 * @brief Function for integer handling
 * 
 * @param dString - pointer to dynamic strung
 * @param token - pointer to token
 * @return INTERNAL_ERR if memory problem occurs
 * @return OK if integer is correct 
 */
int int_handler(DString_t *dString, Token_t *token);


/**
 * @brief Function for double handling
 * 
 * @param dString - pointer to dynamic strung
 * @param token - pointer to token
 * @return INTERNAL_ERR if memory problem occurs
 * @return OK if float is correct 
 */
int float_handler(DString_t *dString, Token_t *token);


/**
 * @brief Part of FSM implemetation, returns FSM STATE according to current state and input char
 *  
 * @param act - current state
 * @param curr - current charachter
 * @param DString - pointer to dynamic string
 * @return FSM state
 */
T_State_t state(T_State_t act, int curr, DString_t *DString);


/**
 * @brief Function that returns the token through the pointer and returns if the token is valid
 * 
 * @param token - pointer to token 
 * @return token through the pointer
 * @return LEX_ERR if lexical error occurs, OK otherwise 
 */
int scan(Token_t *token);

#endif // SCANNER_H
