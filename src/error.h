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

// TODO

typedef struct Status {
    int type;
    int line_num;
} Status_t;

void error_display(int type, int line_num);
// save function return with potential error handling
// TODO just an idea if we want to use it name should be changed
void fr(int code);
