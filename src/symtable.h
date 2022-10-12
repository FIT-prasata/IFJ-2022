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
#include "stack.h"

// Tabulka:
struct htab;  // neúplná deklarace struktury - uživatel nevidí obsah
typedef struct htab htab_t;  // typedef podle zadání

// Prvek:
struct htab_item;
typedef struct htab_item htab_item_t;

// Struktura prvku
struct htab_item {
    int data;  // TODO
    htab_item_t *next;
};

// Struktura tabulky:
struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t **arr_ptr;
};

htab_t *htab_init(size_t n);