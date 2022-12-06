#pragma once

/**
 * @headerfile code_generator.h
 * @project IFJ 2022/2023
 * @variant TRP
 *
 * @brief Code generator for IFJcode22
 *
 * @authors <xsklen14> - David Sklenář
 *          <xproch0o> - Marek Procházka
 *          <xzavad20> - Lukáš Zavadil
 *          <xsvetl07> - Adam Světlík
 */
// TODO: add generate prolog and generate build in functions in main
extern int tmp_var_count;
#define INTERN_VAR_LEN 100

// Local includes
#include "dynamic_string.h"
#include "error.h"
#include "scanner.h"
#include "symtable.h"

/**
 * @brief Frame type
 *
 * @param GF - Global frame
 * @param LF - Local frame
 * @param TF - Temporary frame
 */

#define CHECK_OK(_func) \
    if (_func != OK) return INTERNAL_ERR

#define CHECK_NULL(_func) \
    if (_func == NULL) return INTERNAL_ERR

typedef enum Operation {
    // IF
    IF_LT,
    IF_GT,
    IF_EQ,
    IF_NEQ,
    IF_LEQ,
    IF_GEQ,
    IF_ELSE,
    IF_END,
    // WHILE
    WHILE_LT,
    WHILE_GT,
    WHILE_EQ,
    WHILE_NEQ,
    WHILE_LEQ,
    WHILE_GEQ,
    WHILE_END,
    // ARITHMETIC
    ADD,
    SUB,
    MUL,
    DIV,
    IDIV,
    // LOGICAL
    AND,
    OR,
    NOT,
    // BUILD-IN FUNCTIONS
    WRITE,
    READ,
    IN_STRLEN,
    IN_ORD,
    IN_CHR,
    DEFVAR,
    ASSIGN,
    PROLOG,
    CALL_FUNC,
    CALL_FUNC_ASSIGN,
    DEF_FUNC,
    RETURN,
} Operation_t;

// TODO
void generate_if_start(Operation_t type, char *var1, char *var2, int label,
                       FILE *file);
void generate_else(int label, FILE *file);
/**
 * @brief Generates code for while loop start
 *
 * @param label Label of the while loop
 * @param condition Condition of the while loop
 * @param var1 First variable of the condition
 * @param var2 Second variable of the condition
 * @param file File to write the code to
 */
void generate_while_start(Operation_t type, char *var1, char *var2, int label,
                          FILE *file);

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
// TODO
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
 * @brief Generates code for createframe
 *
 * @param file File to write the code to
 */
void generate_createframe(FILE *file);

/**
 * @brief Generates code for pushframe
 *
 * @param file File to write the code to
 */
void generate_pushframe(FILE *file);

/**
 * @brief Generates code for popframe
 *
 * @param file File to write the code to
 */
void generate_popframe(FILE *file);

/**
 * @brief Generates code for defvar
 *
 * @param var Variable to call
 * @param file File to write the code to
 */
void generate_defvar(char *var, FILE *file);

/**
 * @brief Generates code for call
 *
 * @param label Label to call
 * @param file File to write the code to
 */
void generate_call(char *label, FILE *file);

/**
 * @brief Generates code for return
 *
 * @param file File to write the code to
 */
void generate_return(Symbol_t *func, Symbol_type_t type, char *attribute,
                     FILE *file);

/**
 * @brief Generates code for pushs
 *
 * @param var Variable to write
 * @param file File to write the code to
 */
void generate_pushs(char *var, FILE *file);

/**
 * @brief Generates code for pops
 *
 * @param var Variable to write
 * @param file File to write the code to
 */
void generate_pops(char *var, FILE *file);

/**
 * @brief Generates code for clears
 *
 * @param file File to write the code to
 */
void generate_clears(FILE *file);

/**
 * @brief Generates code for int2float
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_int2float(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for float2int
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_float2int(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for int2char
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_int2char(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for stri2int
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_stri2int(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for read
 *
 * @param var Variable to write
 * @param type Type of variable
 * @param file File to write the code to
 */
void generate_read(char *var, char *type, FILE *file);

/**
 * @brief Generates code for write
 *
 * @param var Variable to write
 * @param file File to write the code to
 */
void generate_write(char *var, FILE *file);

/**
 * @brief Generates code for concat
 *
 * @param var1 First variable
 * @param var2 Second variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_concat(char *var1, char *var2, char *destination, FILE *file);

/**
 * @brief Generates code for strlen
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_strlen(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for getchar
 *
 * @param var Variable to read
 * @param pos Position of character
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_getchar(char *var, char *pos, char *destination, FILE *file);

/**
 * @brief Generates code for setchar
 *
 * @param var Variable to write
 * @param pos Position of character
 * @param ch Character to write
 * @param file File to write the code to
 */
void generate_setchar(char *var, char *pos, char *ch, FILE *file);

/**
 * @brief Generates code for type
 *
 * @param source Source variable
 * @param destination Destination variable
 * @param file File to write the code to
 */
void generate_type(char *source, char *destination, FILE *file);

/**
 * @brief Generates code for label
 *
 * @param label Label to call
 * @param file File to write the code to
 */
void generate_label(char *label, FILE *file);

/**
 * @brief Generates code for jump
 *
 * @param label Label to call
 * @param file File to write the code to
 */
void generate_jump(char *label, FILE *file);

/**
 * @brief Generates code for jumpifeq
 *
 * @param label Label to call
 * @param var1 First variable
 * @param var2 Second variable
 * @param file File to write the code to
 */
void generate_jumpifeq(char *label, char *var1, char *var2, FILE *file);

/**
 * @brief Generates code for jumpifneq
 *
 * @param label Label to call
 * @param var1 First variable
 * @param var2 Second variable
 * @param file File to write the code to
 */
void generate_jumpifneq(char *label, char *var1, char *var2, FILE *file);

/**
 * @brief Generates code for exit
 *
 * @param var Variable to write
 * @param file File to write the code to
 */
void generate_exit(char *var, FILE *file);

/**
 * @brief Generates code for break
 *
 * @param file File to write the code to
 */
void generate_break(FILE *file);

/**
 * @brief Generates code for dprint
 *
 * @param var Variable to write
 * @param file File to write the code to
 */
void generate_dprint(char *var, FILE *file);

/**
 * @brief Converts variable from IFJ22 to IFJcode22 format
 *
 * @param item Variable to convert
 * @param frame Frame of the variable
 * @param converted_string Converted string
 *
 * @return status code
 */
int variable_convert(Symbol_t *variable, DString_t *converted_var);

/**
 * @brief Converts constant from IFJ22 to IFJcode22 format
 *
 * @param token Token to convert
 * @param converted_string Converted string
 *
 * @return status code
 */
int const_convert(Symbol_t *constant, DString_t *converted_const);

/**
 * @brief Converts string from IFJ22 to IFJcode22 format
 *
 * @param token Token to convert
 * @param converted_string Converted string
 *
 * @return status code
 */
int string_convert(Symbol_t *string, DString_t *converted_str);

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
int generate_instruction(Operation_t operation, Symbol_t *dest_in,
                         Symbol_t *var_in_1, Symbol_t *var_in_2, int label,
                         FILE *file);
