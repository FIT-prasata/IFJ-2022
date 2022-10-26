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

#define AVG_LEN_MAX 10
#define AVG_LEN_MIN 2

// Tabulka:
struct htab;                 // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;  // typedef podle zadání

typedef const char *htab_key_t;

// Prvek:
struct htab_item;
typedef struct htab_item htab_item_t;

typedef enum { INT, STRING, BOOL, FLOAT, FUNC, UNKNOWN } Id_type_t;

// Struktura prvku
struct htab_item {
    Token_t *token;
    Id_type_t type;
    htab_item_t *next;
};

// Struktura tabulky:
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

htab_t *htab_init(size_t n);
// htab_item_t *htab_item_init(htab_key_t key);
size_t htab_hash_function(const char *str);
bool htab_insert_item(htab_t *t, Token_t *token);
void print_table(htab_t *t);
htab_item_t *htab_find(htab_t *t, htab_key_t key);
htab_item_t *htab_lookup_add(htab_t *t, Token_t *token);
bool htab_erase(htab_t *t, htab_key_t key);
void htab_clear(htab_t *t);
void htab_free(htab_t *t);
void htab_resize(htab_t *t, size_t newn);
