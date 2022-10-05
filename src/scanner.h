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

// LOCAL INCLUDES
#include "error.h"

// TODO: enum of FSM (DFA) states - will implement after completing design of FSM on paper

// Token types 
typedef enum{
    // OPERATORS, ordered from highest precedence to lowest
    T_MUL,  // multiplication - *
    T_DIV,  // division - /
    T_ADD,  // addition - +
    T_SUB,  // subtraction - -
    T_LT,   // lower than - <
    T_GT,   // greater than - >
    T_LTE,  // lower or equal than - <=
    T_GTE,  // greater or equal than - >=
    T_EQ,   // equal - ===
    T_NEQ   // not equal - !==
    // TODO: add rest of tokens
} T_type;

// Token attribute
typedef union{
    char *string;
    int value;
    double dec_value;
} T_attribute;


// Token struct
typedef struct{
    T_type type; // type of token, one of T_type constants
    T_attribute attribute; // attribute of token
} Token_t;