#pragma once

#ifndef _PARSER_H_
#define _PARSER_H_

// Filename: parser.h
// IFJ 2022/2023 project
// TRP variant
//
// Parser for syntax analysis - header file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// EXTERNAL INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// line counting
extern int line_num;

// LOCAL INCLUDES
#include "code_generator.h"
#include "error.h"
#include "expr.h"
#include "scanner.h"
#include "symtable.h"

// Location of expression
#define EXPR_LOC_RET 100
#define EXPR_LOC_COND 101
#define EXPR_LOC_ASSIGN 102

// scope check
typedef struct {
    bool in_func;
    bool in_while;
    bool in_if;
    bool in_else;
    bool in_global;
    int count_if;
    int count_while;
    int num_if;
    int num_while;
} scope_t;

// Function prototypes
Token_t *init_token(void);
int free_token(Token_t *token);

int add_built_in(Htab_t *global_table);

/**
 * @brief main function for parsing
 * @return void
 */
int parse(void);

/**
 * @brief   RULES
 *          <PROGRAM> -> <DEFFUNC> <PROGRAM>
 *          <PROGRAM> -> <STAT> <PROGRAM>
 *          <PROGRAM> -> EOF
 *
 * @param current_token
 * @param global_table
 *
 * @return int - error code
 */
int program_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table);

/**
 * @brief   RULES
 *          <DEFFUNC> -> K_FUNC T_FUNC_ID T_LBR <ARG> T_COL <TYPE> T_LCBR <STAT>
 * T_RCBR T_RCBR
 *
 * @param current_token
 * @param global_table
 *
 * @return int - error code
 */
int def_func_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table);

/**
 * @brief   RULES
 *          <ARG> -> <TYPE> <PARAM> <ARGLIST>
 *          TODO: still can have const in funcdef :((
 *          <ARG> -> T_RBR
 *
 * @param current_token
 * @param global_table
 * @return
 */
int arg_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   RULES
 *          ARGLIST -> T_COMMA <ARG>
 *          ARGLIST -> T_RBR
 *
 * @param current_token
 * @param global_table
 * @return
 */
int arg_list_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   RULES
 *          <PARAM> -> T_ID
 *          <PARAM> -> <CONST>
 *
 * @param current_token
 * @param global_table
 * @return
 */
int param_rule(Token_t *current_token, Htab_t *global_table, bool func_call);

/**
 * @brief   RULES
 *         <PARAM_LIST> -> T_COMMA <PARAM> <PARAM_LIST>
 *         <PARAM_LIST> -> T_RBR
 * @param current_token
 * @param global_table
 * @return
 */
int param_list_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   RULES
 *          <TYPE> -> K_STRING | K_INT | K_FLOAT | K_NULL
 *
 * @param current_token
 * @param global_table
 * @return
 */
int type_rule(Token_t *current_token, Htab_t *global_table, bool is_func_def, bool is_func_type);

/**
 * @brief   RULES
 *      <CONST> -> T_INT | T_FLOAT | T_STRING | T_NULL
 * @param current_token
 * @param global_table
 * @return
 */
int const_rule(Token_t *current_token, Htab_t *global_table, bool func_call);

/**
 * @brief   RULES
 *          <STAT> -> K_IF T_LBR <EXPR> T_LCBR <STAT> K_ELSE LCBR <STAT>
 *          <STAT> -> K_WHILE T_LBR <EXPR> T_LCBR <STAT>
 *          <STAT> -> K_RET <EXPR> <STAT>
 *
 *          <STAT> -> T_ID T_ASSIGN <ASSIGN_TYPE> <STAT>
 *          <STAT> -> T_ID <TYPE> T_SEM <STAT>
 *          <STAT> -> <FUNC_CALL> T_SEM <STAT>
 *          <STAT> -> T_RCBR
 *          <STAT> -> ε
 *
 * @param current_token
 * @param global_table
 * @return
 */
int stat_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table);

/**
 * @brief   RULES
 *          <ASIGN_TYPE> -> <EXPR>
 *          <ASIGN_TYPE> -> <FUNC_CALL>
 *
 * @param current_token
 * @param global_table
 * @return
 */
int assign_type_rule(Token_t *current_token, scope_t *scope_state, Htab_t *global_table);

/**
 * @brief   RULES
 *          <FUNC_CALL> -> T_FUNC_ID T_LBR <PARAM> <PARAM_LIST>
 *
 * @param current_token
 * @param global_table
 * @return
 */
int func_call_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief EXPR -> precedent analysis -> bottom up parser
 *
 * @param current_token
 * @param global_table
 * @return
 */
int expr_rule(Token_t *current_token, Htab_t *global_table, int location, scope_t *scope_state);

#endif  // _PARSER_H_
