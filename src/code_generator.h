#pragma once

// Filename: code_generator.h
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

#include "dynamic_string.h"
#include "error.h"
#include "scanner.h"
#include "symtable.h"

// Frame types
typedef enum { GF, LF, TF } Frame_t;

/**
 * @brief Generates code for while loop start
 *
 * @param label Label of the while loop
 * @param condition Condition of the while loop
 * @param var1 First variable of the condition
 * @param var2 Second variable of the condition
 * @param file File to write the code to
 */
void generate_while_start(int label, char *condition, char *var1, char *var2, FILE *file);

/**
 * @brief Generates code for while loop end
 *
 * @param label Label of the while loop
 * @param file File to write the code to
 */
void generate_while_end(int label, FILE *file);

/**
 * @brief Generates code for if statement start
 *
 * @param label Label of the if statement
 * @param condition Condition of the if statement
 * @param var1 First variable of the condition
 * @param var2 Second variable of the condition
 * @param file File to write the code to
 */
void generate_if_start(int label, char *condition, char *var1, char *var2, FILE *file);

/**
 * @brief Generates code for if statement end
 *
 * @param label Label of the if statement
 * @param file File to write the code to
 */
void generate_if_end(int label, FILE *file);

/**
 * @brief Generates code for function prolog
 *
 * @param file File to write the code to
 */
void generate_prolog(FILE *file);

/**
 * @brief Generates code for addition
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_add(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for subtraction
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_sub(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for multiplication
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_mul(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for division
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_div(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for integer division
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_idiv(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for move
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_move(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for lower than
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_lt(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for greater than
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_gt(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for equal to
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_eq(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for and
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_and(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for or
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_or(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for not
 *
 * @param var1 First variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_not(char *var1, char *destination, FILE *file);

/**
 * @brief Converts variable from IFJ22 to IFJcode22 format
 *
 * @param item Variable to convert
 * @param frame Frame of the variable
 *
 * @return char* Converted variable
 */
char *variable_convert(Htab_item_t *item, Frame_t frame);

/**
 * @brief Converts constant from IFJ22 to IFJcode22 format
 *
 * @param token Token to convert
 *
 * @return char* Converted constant
 */
char *const_convert(Token_t *token);

/**
 * @brief Converts string from IFJ22 to IFJcode22 format
 *
 * @param token Token to convert
 *
 * @return char* Converted string
 */
char *string_convert(Token_t *token);

/**
 * @brief Generates IFJcode22 code
 *
 * @param operation Operation to generate code for
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 *
 * @return status code
 *
 * @todo not implemented yet
 */
int generate(T_type_t operation, char *var1, char *var2, char *destination, FILE *file);