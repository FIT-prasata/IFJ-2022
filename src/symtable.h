#pragma once

/**
 * @headerfile symtable.h
 * @project IFJ 2022/2023
 * @variant TRP
 *
 * @brief Symbol table for IFJcode22
 *
 * @authors <xsklen14> - David Sklenář
 *          <xproch0o> - Marek Procházka
 *          <xzavad20> - Lukáš Zavadil
 *          <xsvetl07> - Adam Světlík
 */

#ifndef _SYMTABLE_H_
#define _SYMTABLE_H_

// LOCAL INCLUDES
#include <stdint.h>

#include "scanner.h"
#include "stack.h"

// line counting
extern int line_num;

/**
 * @brief Predeclared types
 */
typedef struct Htab_item Htab_item_t;
typedef struct Symbol Symbol_t;

/**
 * @brief Variable types
 * @note Used in Symbol_t
 */
typedef enum Value_type { INT, STRING, BOOL, FLOAT, NIL } Value_type_t;

// TODO: add comment to frame + update symbol_t comment
typedef enum Frame { GF, LF, TF, UNDEF } Frame_t;

/**
 * @brief Variable structure
 *
 * @param type Variable type
 * @param asigned Variable asigned
 *
 * @note Used in Symbol_t
 */
typedef struct Var {
    Value_type_t var_type;
    bool asigned;
    Frame_t frame;
    bool used;
} Var_t;

/**
 * @brief Function structure
 *
 * @param argc Number of arguments
 * @param argv Array of arguments
 * @param return_type Return type
 * @param defined Function defined
 *
 * @note Used in Symbol_t
 */
typedef struct Function {
    int argc;
    Symbol_t *argv;
    Value_type_t return_type;
    bool defined;
    bool used;
} Func_t;

/**
 * @brief Symbol types
 *
 * @param var Variable0
 * @param func Function
 */
typedef enum Symbol_type { VARIABLE, FUNCTION, CONSTANT } Symbol_type_t;

/**
 * @brief Symbol structure
 *
 * @param name Symbol name
 * @param type Variable or function
 * @param used for unused variable warning
 * @param next Pointer to the next symbol
 *
 * @note Used in Htab_item_t
 */
typedef struct Symbol {
    char *attribute;
    Symbol_type_t symbol_type;
    Var_t *var;
    Func_t *func;
    Value_type_t const_type;
    Symbol_t *next;
} Symbol_t;

/**
 * @brief Hashtable key type
 */
typedef const char *Htab_key_t;

/**
 * @brief Hashtable item structure
 *
 * @param data Symbol
 * @param next Pointer to the next item
 */
typedef struct Htab_item {
    Symbol_t data;
    Htab_item_t *next;
} Htab_item_t;

/**
 * @brief Hashtable structure
 *
 * @param size Number of items in the table
 * @param arr_size Size of the array
 * @param arr_ptr Pointer to the array
 */
typedef struct Hashtable {
    size_t size;
    size_t arr_size;
    Htab_item_t **arr_ptr;
} Htab_t;

/**
 * @brief Hashtable constructor - initializes hashtable
 *
 * @param size - size of hashtable
 *
 * @return - pointer to table when success
 * @return - NULL when failed
 */
Htab_t *htab_init(size_t size);

/**
 * @brief Hash function - hash % array size gives table index of item
 *
 * @param key - key to hash
 *
 * @return - hash value
 */
int htab_hash_function(Htab_key_t key);

/**
 * @brief Inserts item into the hashtable
 *
 * @param table - pointer to hashtable
 * @param token - pointer to token
 *
 * @return - INTERNAL_ERR when failed
 * @return - SUCCESS when success
 */
int htab_insert_item(Htab_t *table, Token_t *token);

/**
 * @brief Finds item in table according to the entered key
 *
 * @param table - hashtable
 * @param key   - key
 *
 * @return - pointer to item when success
 * @return - NULL when failed
 */
Htab_item_t *htab_find(Htab_t *table, Htab_key_t key);

/**
 * @brief Finds or instert item in table according to the entered key
 *
 * @param table - hashtable
 * @param token - token
 *
 * @return - when item is found, returns pointer to item
 * @return - when item is not found, inserts item into the hashtable and returns
 *           pointer to item
 * @return - NULL when failed
 */
Htab_item_t *htab_lookup_add(Htab_t *table, Token_t *token);

/**
 * @brief Deletes item from hashtable according to the entered key
 *
 * @param table - hashtable
 * @param key   - key
 *
 * @return - status code
 */
int htab_erase(Htab_t *table, Htab_key_t key);

/**
 * @brief Deletes all items from hashtable
 *
 * @param table - hashtable
 *
 * @return - status code
 */
int htab_clear(Htab_t *table);

/**
 * @brief Hashtable destructor - deletes all items and frees allocated memory
 *
 * @param table - hashtable
 *
 * @return - status code
 */
int htab_free(Htab_t *table);

#endif  // _SYMTABLE_H_