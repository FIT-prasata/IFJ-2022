#pragma once

// Filename: error.h
// IFJ 2022/2023 project
// TRP variant
//
// Error handler - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// EXTERNAL INCLUDES
#include <stdlib.h>

// LOCAL INCLUDES
#include "scanner.h"

// Specification defined erros
#define OK 0
#define LEX_ERR 1         // Lexical analysis error
#define SYNTAX_ERR 2      // Syntax analysis error
#define UNDEF_FUNC_ERR 3  // Undefined function / redefinition
#define FUNC_TYPE_ERR 4   // Incorrect function parameter(s) / return type
#define UNDEF_VAR_ERR 5   // Undefined variable
#define RET_ERR 6         // Function return syntax error
#define EXPR_TYPE_ERR 7   // Expression type incompatibility
#define OTHER_ERR 8       // Other semantics errors
#define INTERNAL_ERR 99   // Internal compiler error (memory allocation)

// Custom errors
#define NOT_IMPLEMENTED 100
#define LC_EOF_ERR 11
#define BC_EOF_ERR 12
#define NUM_ERR 13
#define STR_ERR 14
#define EQ_ERR 15
#define NE_ERR 16
#define TYPE_ERR 17
#define ID_ERR 18

typedef struct Status {
    int type;
    int line_num;
} Status_t;

void error_display(int type, int line_num);
// save function return with potential error handling

// TODO just an idea if we want to use it name should be changed
// Wrapper for functions returning error code
// param: code - error code (int)
// either is OK(0) or executes error_display and exits with proper error code
void try(int code);

// Raise error
// param: type - error type (int)
void raise(int code);
