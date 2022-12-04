#pragma once

#ifndef EXPR_H
#define EXPR_H

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

#define P_TABLE_SIZE 15  // Size of precedence table
#define EOEXPR 999       // End of expression

// Precedence table
//
// [ - shift
// ] - reduce
// = - special shift
// ! - error
char ptable[P_TABLE_SIZE][P_TABLE_SIZE] = {
    /*
      STACK | INPUT -->
        |
        v       $    i    +    -    *    /    .   ===  !==   <    >    <=   >=
      (    ) */
    /*  $  */ {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[',
               '[', '!'},
    /*  i  */
    {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!', ']'},
    /*  +  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  -  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  *  */
    {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  /  */
    {']', '[', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /*  .  */
    {']', '[', ']', ']', '[', '[', ']', ']', ']', ']', ']', ']', ']', '[', ']'},
    /* === */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /* !== */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  <  */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  >  */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  <= */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  >= */
    {']', '[', '[', '[', '[', '[', '[', '!', '!', '!', '!', '!', '!', '[', ']'},
    /*  (  */
    {'!', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '[', '='},
    /*  )  */
    {']', '!', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', ']', '!',
     ']'}};

// Deciding what precedence table operation is next
typedef enum {
    EXPR_SHIFT,
    EXPR_REDUCE,
    EXPR_SPECIAL_SHIFT,
    EXPR_ERROR
} ptable_move_t;

// Precedence table navigation
typedef enum {
    EXPR_STACK_BOTTOM,  // Stack bottom '$'
    EXPR_ID,            // Identifier 'i'
    EXPR_ADD,           // Addition '+'
    EXPR_SUB,           // Subtraction '-'
    EXPR_MUL,           // Multiplication '*'
    EXPR_DIV,           // Division '/'
    EXPR_DOT,           // Dot '.'
    EXPR_EQ,            // Equality '==='
    EXPR_NEQ,           // Inequality '!=='
    EXPR_LT,            // Less than '<'
    EXPR_GT,            // Greater than '>'
    EXPR_LE,            // Less than or equal '<='
    EXPR_GE,            // Greater than or equal '>='
    EXPR_LBR,           // Left bracket '('
    EXPR_RBR            // Right bracket ')'
} ptable_symbol_t;

// Evaluates next move from precedence table based on top terminal on stack and
// current input symbol
// 1. Check if both indexes are in the boundaries of the precedence table
// 2. Return corresponding move from move enum
ptable_move_t ptable_get_next_move(ptable_symbol_t stack,
                                   ptable_symbol_t input);

// Returns precedence table symbol based on top terminal on stack
ptable_symbol_t ptable_get_symbol_from_char(char c);

// Returns terminal based on precedence table symbol
char ptable_get_char_from_symbol(ptable_symbol_t symbol);

// Shift operation
// 1. Push '[' char on top of the closest terminal on stack - TODO Luke -> stack
// for expressions
// 2. Push input char on top of the stack
// 3. Return status code
int expr_shift(/* TODO - ADD stack */ char c);

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
int expr_reduce(/* TODO - ADD both stacks and token */);

// Special shift operation
// 1. Push terminal on stack
// 2. Return status code
int expr_special_shift(/* TODO - ADD stack */ char c);

// Compares right hand side of expression rules with given string (rule)
// 1. Loop over 2D array of rules and see if any of them matches input string
// 2. Return status code
int is_valid_rule(/* TODO - ADD dynamic string */);

// Loads the whole expression and push its tokens to token stack
int expr_load(/* TODO - ADD symbtable, token and possibly other parameters*/);

// Main function for expression parsing
// 1. Initialize stacks
// 2. Load expression -> expr_load()
// 3. Parse loaded expression -> expr_parse()
// 4. Generate code based on the location of expression -> switch case statement
int expr_main(
    /* TODO - ADD symtable, token and possibly other needed parameters*/);

// Parses loaded expression
// 1. Map token type to precedence table symbol enum
// 2. Get terminal terminal from top of the stack and call
// ptable_get_symbol_from_char()
// 3. Call ptable_get_next_move() with result symbol from function call as its
// input
// 4. Based on the result of the function call, call expr_shift(),
// expr_reduce(), expr_special_shift()
int expr_parse(
    /* TODO - ADD both stacks, token and possibly other needed parameters*/);

#endif