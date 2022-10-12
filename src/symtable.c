// Filename: symtable.c
// IFJ 2022/2023 project
// TRP variant
//
// Symtable
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "symtable.h"

// Konstruktor tabulky - vytvoří a inicializuje tabulku
// Vrací ukazatel na tabulku při úspěchu, jinak NULL
// PARAMS: n - velikost hashovací tabulky
htab_t *htab_init(size_t n) {
    if (n < 1) return NULL;

    // Alokace paměti pro strukturu tabulky
    htab_t *htab_table = malloc(sizeof(htab_t));

    if (htab_table == NULL) return NULL;

    htab_table->size = 0;
    htab_table->arr_size = n;

    // Alokace paměti pro pole prvků
    htab_table->arr_ptr = malloc(n * sizeof(htab_item_t *));

    if (htab_table->arr_ptr == NULL) return NULL;

    for (size_t i = 0; i < n; i++) htab_table->arr_ptr[i] = NULL;

    return htab_table;
}


