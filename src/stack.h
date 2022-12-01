#pragma once

#ifndef _STACK_H_
#define _STACK_H_

// Filename: stack.h
// IFJ 2022/2023 project
// TRP variant
//
// Stack implementation for FA - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// EXTERNAL INCLUDES
#include <limits.h>  // temporary import for INT_MIN constant
#include <stdlib.h>

// LOCAL INCLUDES
#include "scanner.h"  // for accessing token struct later on
#include "error.h"    // for status codes

// line counting
extern int line_num;

// DEFINES
#define EMPTY_STACK INT_MIN
#define NO_TYPE INT_MAX

typedef struct Token_stack Token_stack_t;

typedef struct Token_stack {
    Token_t head;         // last pushed token (top of stack)
    Token_stack_t *next;  // pointer to next token
} Token_stack_t;

int token_stack_init(Token_stack_t *t_stack);
Token_t token_stack_get_head(Token_stack_t *t_stack);
void token_stack_push(Token_stack_t *t_stack, Token_t token);
int token_stack_pop(Token_stack_t *t_stack);
void token_stack_clear(Token_stack_t *t_stack);

#endif // _STACK_H_
