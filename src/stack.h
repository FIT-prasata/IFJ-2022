#pragma once

#ifndef _STACK_H_
#define _STACK_H_

// Filename: stack.h
// IFJ 2022/2023 project
// TRP variant
//
// Stack implementations for expression parsing - header file
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
#include "expr.h"     // for expression enums

// DEFINES
#define EMPTY_STACK INT_MIN
#define NO_TYPE INT_MAX
#define CHAR_STACK_BOTTOM '$'
#define CHAR_STACK_NO_MATCH -1
#define TERMINALS_NUM 16

// Line counting
extern int line_num;

// TOKEN STACK

typedef struct Token_stack Token_stack_t;

typedef struct Token_stack {
    Token_t token_head;         // Last pushed token (top of token stack)
    Token_stack_t *next_token;  // Pointer to next token
} Token_stack_t;

// Initializes token stack
int token_stack_init(Token_stack_t *t_stack);

// Returns token that is currently on top of the token stack 
Token_t token_stack_get_head(Token_stack_t *t_stack);

// Pushes token into the stack
int token_stack_push(Token_stack_t *t_stack, Token_t token);

// Pops token from the stack
int token_stack_pop(Token_stack_t *t_stack);

// Might be useful for debugging
void token_stack_clear(Token_stack_t *t_stack);

// CHARACTER STACK

typedef struct Char_stack Char_stack_t;

typedef struct Char_stack {
    char char_head;           // Last pushed character (top of character stack)
    Char_stack_t *next_char;  // Pointer to next character
} Char_stack_t;

// Initializes character stack
int char_stack_init(Char_stack_t *c_stack);

// Returns character that is currently on top of the character stack
char char_stack_get_head(Char_stack_t *c_stack);

// Pushes character into the character stack
int char_stack_push(Char_stack_t *c_stack, char character);

// Pops character from the character stack
int char_stack_pop(Char_stack_t *c_stack);

// Might be useful for debugging
void char_stack_clear(Char_stack_t *c_stack);

// Get the closest terminal on top of the character stack
char char_stack_get_closest_terminal(Char_stack_t *c_stack);

// Pushes '[' character into the character stack to the right of the closest terminal
int char_stack_push_shift(Char_stack_t *c_stack);

#endif // _STACK_H_