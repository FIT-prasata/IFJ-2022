#pragma once

// Filename: scanner.c
// IFJ 2022/2023 project
// TRP variant
//
// Scanner for lexical analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "scanner.h"
#include "stack.h"

// Predeclared types
typedef struct Htab_item Htab_item_t;
typedef struct Symbol Symbol_t;

// Variable types
typedef enum { INT, STRING, BOOL, FLOAT, NONE } Var_type_t;

// Variable structure
typedef struct Var {
    Var_type_t type; // Type of the variable
    bool asigned;    // true if variable has been asigned
} Var_t;

// Function structure
typedef struct Function {
    int argc;               // Number of arguments
    Var_type_t *argv;       // Array of argument types
    Var_type_t return_type; // Return type
    bool defined;           // true if function is defined, false if only declared
} Func_t;

// Symbol types
typedef union {
    Var_t var;    // Variable
    Func_t func;  // Function
} Symbol_type_t;

// Symbol structure
typedef struct Symbol {
    const char *name;   // Name of the symbol
    Symbol_type_t type; // Variable or function
    bool used;          // for unused variable warning
    Symbol_t *next;     // Pointer to the next symbol
} Symbol_t;


// Hashtable key type
typedef const char *Htab_key_t;

// Hashtable item structure
typedef struct Htab_item {
    Symbol_t data;
    Htab_item_t *next;
} Htab_item_t;

// Hashtable structure
typedef struct Hashtable {
    size_t size;           // number of items in the table
    size_t arr_size;       // size of the array
    Htab_item_t **arr_ptr; // pointer to the array
} Htab_t;



/**
 * Hashtable constructor - initializes hashtable
 * @param size - size of hashtable
 * @return - pointer to table when success
 * @return - NULL when failed
 */
Htab_t *htab_init(size_t size);

/**
 * Hash function - hash % array size gives table index of item
 * @param key - key to hash
 * @return - hash value
 */
int htab_hash_function(Htab_key_t key);

/**
 * Inserts item into the hashtable
 * @param table - pointer to hashtable
 * @param token - pointer to token
 * @return - INTERNAL_ERR when failed
 * @return - SUCCESS when success
 */
int htab_insert_item(Htab_t *table, Token_t *token);

/**
 * Finds item in table according to the entered key
 * @param table - hashtable
 * @param key   - key
 * @return - pointer to item when success
 * @return - NULL when failed
 */
Htab_item_t *htab_find(Htab_t *table, Htab_key_t key);

/**
 * Finds or instert item in table according to the entered key
 * @param table - hashtable
 * @param token - token
 * @return - when item is found, returns pointer to item
 * @return - when item is not found, inserts item into the hashtable and returns
 *           pointer to item
 * @return - NULL when failed
 */
Htab_item_t *htab_lookup_add(Htab_t *table, Token_t *token);

/**
 * Deletes item from hashtable according to the entered key
 * @param table - hashtable
 * @param key   - key
 * @return - status code
 */
int htab_erase(Htab_t *table, Htab_key_t key);

/**
 * Deletes all items from hashtable
 * @param table - hashtable
 * @return - status code
 */
int htab_clear(Htab_t *table);

/**
 * Hashtable destructor - deletes all items and frees allocated memory
 * @param table - hashtable
 * @return - status code
 */
int htab_free(Htab_t *table);
