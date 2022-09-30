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

#pragma once

// EXTERNAL INCLUDES
#include <limits.h> // temporary import for INT_MIN constant
#include <stdlib.h>
#include <stdio.h>

// LOCAL INCLUDES
#include "scanner.h" // for accessing token struct later on

// DEFINES
#define EMPTY_STACK INT_MIN
#define NO_TYPE INT_MAX

typedef struct Stack Stack_t;

// !!! DUMMY STRUCT -> REPLACE WITH PROPER TOKEN STRUCT DEFINED IN SCANNER !!!
typedef struct Token {
    int type;
    int value;
} Token_t;

typedef struct Stack {
    Token_t head;   // last pushed token (top of stack)
    Stack_t *next;  // pointer to next token
} Stack_t;

void stack_init(Stack_t *stack);
Token_t stack_get_head(Stack_t *stack);
int stack_push(Stack_t *stack, Token_t token);
int stack_pop(Stack_t *stack);
void stack_clear(Stack_t *stack);