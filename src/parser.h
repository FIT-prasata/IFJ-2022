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
 * @brief handler of PROGRAM rule
 * @param current_token
 * @param global_table
 * @return
 */
int program_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of DEFVAR rule
 * @param current_token
 * @param global_table
 * @return
 */
int def_var_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of DEFFUN rule
 * @param current_token
 * @param global_table
 * @return
 */
int def_func_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of ARG rule
 * @param current_token
 * @param global_table
 * @return
 */
int arg_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of ARGLIST rule
 * @param current_token
 * @param global_table
 * @return
 */
int arg_list_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of PARAM rule
 * @param current_token
 * @param global_table
 * @return
 */
int param_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of TYPE rule
 * @param current_token
 * @param global_table
 * @return
 */
int type_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of STAT rule
 * @param current_token
 * @param global_table
 * @return
 */
int stat_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of STATLIST rule
 * @param current_token
 * @param global_table
 * @return
 */
int stat_list_rule(Token_t *current_token,Htab_t* global_table);

/**
 * @brief handler of EXPR rule
 * @param current_token
 * @param global_table
 * @return
 */
int expr_rule(Token_t *current_token,Htab_t* global_table);