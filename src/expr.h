#pragma once

#ifndef _EXPR_H_
#define _EXPR_H_

// Filename: expr.h
// IFJ 2022/2023 project
// TRP variant
//
// Bottom up parser header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "code_generator.h"
#include "dynamic_string.h"
#include "parser.h"
#include "scanner.h"
#include "stack.h"
#include "symtable.h"

#define P_TABLE_SIZE 15   // Size of precedence table
#define EOEXPR 999        // End of expression
#define RULES_NUM 13      // Number of rules
#define MAX_RULE_LEN 4    // Maximum length of rule (in chars)
#define EXPR_NONTERM 'E'  // Nonterminal symbol

// Deciding what precedence table operation is next
typedef enum { EXPR_SHIFT, EXPR_REDUCE, EXPR_SPECIAL_SHIFT, EXPR_ERROR } ptable_move_t;

// Evaluates next move from precedence table based on top terminal on stack and
// current input symbol
// 1. Check if both indexes are in the boundaries of the precedence table
// 2. Return corresponding move from move enum
ptable_move_t ptable_get_next_move(ptable_symbol_t stack, ptable_symbol_t input);

// Shift operation
// 1. Push '[' char on top of the closest terminal on stack - TODO Luke -> stack
// for expressions
// 2. Push input char on top of the stack
// 3. Return status code
int expr_shift(Char_stack_t *c_stack, char character);

// Reduce operation
// 1. Get top terminal on stack
// 2. Generate code based on given terminal
// 3. Keep popping stack until you get the '[' char or the stack is empty and
// save chars to a dynamic string
// 4. Compare constructed string with right hand sides of expression rules
// 5. Free dynamic string
// 6. Check if the string matches any of the rules
// 7. Push the left hand side of the rule on top of the stack ('E')
// 8. Return status code
int expr_reduce(Htab_t *table, Char_stack_t *c_stack, Token_stack_t *t_stack);

// Special shift operation
// 1. Push terminal on stack
// 2. Return status code
int expr_special_shift(Char_stack_t *c_stack, char character);

// Compares right hand side of expression rules with given string (rule)
// 1. Loop over 2D array of rules and see if any of them matches input string
// 2. Return status code
int is_valid_rule(DString_t *d_string);

// Main function for expression parsing
// 1. Initialize stacks
// 2. Load expression -> expr_load()
// 3. Parse loaded expression -> expr_parse()
// 4. Generate code based on the location of expression -> switch case statement
int expr_main(Htab_t *table, Token_t *token, int location);

// Parses loaded expression
// 1. Map token type to precedence table symbol enum
// 2. Get terminal terminal from top of the stack and call
// ptable_get_symbol_from_char()
// 3. Call ptable_get_next_move() with result symbol from function call as its
// input
// 4. Based on the result of the function call, call expr_shift(),
// expr_reduce(), expr_special_shift()
int expr_parse(Htab_t *table, Char_stack_t *c_stack, Token_stack_t *t_stack, Token_t *token, int location);

// Generates instruction when reducing
int expr_instr_gen(Htab_t *table, Token_stack_t *t_stack, char term);

// Validates first token of expression
int expr_validate_first(Token_t *token);

#endif  // _EXPR_H_