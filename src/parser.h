#pragma once

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

// LOCAL INCLUDES
#include "error.h"
#include "scanner.h"
#include "symtable.h"

// Function prototypes
Token_t *init_token(void);
void free_token(Token_t *token);

/**
 * @brief main function for parsing
 * @return void
 */
int parse(void);

/**
 * @brief   PROGRAM -> DEFVAR PROGRAM
 *          PROGRAM -> DEFUNC PROGRAM
 *          PROGRAM -> STAT PROGRAM
 *          PROGRAM -> EOF
 *
 * @param current_token
 * @param global_table
 *
 * @return int - error code
 */
int program_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   TODO
 *
 * @param current_token
 * @param global_table
 *
 * @return int - error code
 */
int def_var_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   DEFFUNC -> function f_id ( ARG : TYPE { STAT
 *
 * @param current_token
 * @param global_table
 *
 * @return int - error code
 */
int def_func_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   ARG -> TYPE PARAM ARGLIST
 *
 * @param current_token
 * @param global_table
 * @return
 */
int arg_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   ARGLIST -> , PARAM ARGLIST
 *          ARGLIST -> ')'
 *
 * @param current_token
 * @param global_table
 * @return
 */
int arg_list_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   PARAM -> var_id
 *          PARAM -> const
 *
 * @param current_token
 * @param global_table
 * @return
 */
int param_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   TYPE -> string
 *          TYPE -> int
 *          TYPE -> float
 *          TYPE -> null
 *
 * @param current_token
 * @param global_table
 * @return
 */
int type_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   STAT -> id = ASSIGN_TYPE STATLIST
 *          STAT ->  if ( EXPR ) { STAT STATLIST else { STAT STATLIST
 *          STAT -> while ( EXPR ) { STAT STATLIST
 *
 * @param current_token
 * @param global_table
 * @return
 */
int stat_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   ASIGN_TYPE -> EXPR
 *          ASIGN_TYPE -> FUNC_CALL
 *
 * @param current_token
 * @param global_table
 * @return
 */
int assign_type_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief  function f_id ( ARG
 *
 * @param current_token
 * @param global_table
 * @return
 */
int func_call_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief   STATLIST -> ; STAT STATLIST
 *          STATLIST -> '}'
 *
 *
 * @param current_token
 * @param global_table
 * @return
 */
int stat_list_rule(Token_t *current_token, Htab_t *global_table);

/**
 * @brief EXPR -> precedent analysis -> bottom up parser
 *
 * @param current_token
 * @param global_table
 * @return
 */
int expr_rule(Token_t *current_token, Htab_t *global_table);
