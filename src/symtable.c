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

#include <stdint.h>

#include "string.h"

// Hashtable constructor - initializes hashtable
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



// Hashovací funkce - její výsledek modulo arr_size určuje index do tabulky
// PARAMS: str - řetězec
size_t htab_hash_function(const char *str) {
    uint32_t h = 0;
    const unsigned char *p;

    for (p = (const unsigned char *)str; *p != '\0'; p++) h = 65599 * h + *p;

    return h;
}

// Vkládá prvek do tabulky
// Vrací true při úspěchu, jiank false
// PARAMS: t - hashovací tabulka
//         key - klíč
bool htab_insert_item(htab_t *t, Token_t *token) {
    htab_key_t key = token->attribute.string;
    int hash = htab_hash_function(key) % t->arr_size;

    // Inicializace prvku
    htab_item_t *item = malloc(sizeof(htab_item_t));
    if (item == NULL) return false;

    item->token = token;
    item->type = UNKNOWN;
    item->next = NULL;

    // Doplnění hodnot do prvku a do hashovací tabulky
    htab_item_t *tmp = t->arr_ptr[hash];
    t->arr_ptr[hash] = item;
    item->next = tmp;
    t->size++;

    return true;
}

htab_item_t *htab_find(htab_t *t, htab_key_t key) {
    int hash = htab_hash_function(key) % t->arr_size;
    htab_item_t *item = t->arr_ptr[hash];

    // Prohledávání tabulky
    while (item != NULL && strcmp(item->token->attribute.string, key) != 0) {
        item = item->next;
    }
    if (item == NULL) return NULL;

    return item;
}

htab_item_t *htab_lookup_add(htab_t *t, Token_t *token) {
    htab_key_t key = token->attribute.string;
    htab_item_t *item = htab_find(t, key);
    if (item == NULL) {
        if (htab_insert_item(t, token) == false) return NULL;

        item = htab_find(t, key);

        return item;
    }
    return item;
}

// Vymaže prvek z tabulky podle zadaného klíče
// Vrací true při vymazání prvku, jinak false
// PARAMS: t - hashovací tabulka
//         key - klíč
bool htab_erase(htab_t *t, htab_key_t key) {
    int hash = htab_hash_function(key) % t->arr_size;
    htab_item_t *item = t->arr_ptr[hash];
    htab_item_t *pervious = NULL;

    // Prohledávání tabulky
    while (item != NULL && strcmp(item->token->attribute.string, key)) {
        pervious = item;
        item = item->next;
    }

    // Nenalezení klíče
    if (item == NULL) {
        fprintf(stderr, "Chyba pri mazani\n");
        return false;
    }

    // Předání ukazatele následujícího prvku předchozímu ukazateli
    if (pervious == NULL) {
        t->arr_ptr[hash] = item->next;
    } else {
        pervious->next = item->next;
    }

    // Uvolnění paměti
    free(item);
    t->size--;


    return true;
}

// Vymaže všchny prvky v tabulce
// PARAMS: t - hashovací tabulka
void htab_clear(htab_t *t) {
    for (size_t i = 0; i < t->arr_size; i++) {
        size_t size = t->arr_size;
        htab_item_t *item = t->arr_ptr[i];

        while (item != NULL) {
            htab_erase(t, item->token->attribute.string);
            item = item->next;
        }
    }
    t->size = 0;
}

// Destruktor tabulky - vymaže všechny prvky a uvolní pamět
// PARAMS: t - hashovací tabulka
void htab_free(htab_t *t) {
    htab_clear(t);

    free(t->arr_ptr);

    free(t);
}


void print_table(htab_t *t) {
    const char *enum_type[6] = {"INT",   "STRING", "BOOL",
                                "FLOAT", "FUNC",   "UNKNOWN"};
    const char *enum_types2[] = {
        // OPERATORS, ordered from highest precedence to lowest
        "T_LT",  // <
        "T_GT",  // >
        "T_LE",  // <=
        "T_GE",  // >=
        "T_EQ",  // ===
        "T_NE",  // !==

        // KEYWORDS
        "T_ELSE",   // else
        "T_FLOAT",  // float
        "T_FUNC",   // function
        "T_IF",     // if
        "T_INT",    // int
        "T_NULL",   // null
        "T_RET",    // return
        "T_STR",    // string
        "T_VOID",   // void
        "T_WHILE",  // while

        // PUNCTUATORS
        "T_LCBR",    // {
        "T_RCBR",    // }
        "T_LBR",     // (
        "T_RBR",     // )
        "T_SEMCOL",  // ;
        "T_COL",     // :
        "T_CONCAT",  // .

        // EXPRESSIONS
        "T_MUL",     // *
        "T_DIV",     // /
        "T_ADD",     // +
        "T_SUB",     // -
        "T_ASSIGN",  // =
        "T_NEG",     // !

        // OTHERS
        "T_ID",    // identifier
        "T_EOF",   // end of file
        "T_EOL",   // end of line
        "T_UNDEF"  // undefined type

    };
    printf("Start of htab \n");
    for (int i = 0; i < (int)t->arr_size; i++) {
        if (t->arr_ptr[i] == NULL) {
            printf("\t%i\t---\n", i);
        } else {
            printf("\t%i\t ", i);
            htab_item_t *tmp = t->arr_ptr[i];
            while (tmp != NULL) {
                printf("[ID_type: %s, Attribute: %s, Token_type: %s] - ",
                       enum_type[tmp->type], tmp->token->attribute.string,
                       enum_types2[tmp->token->type]);
                tmp = tmp->next;
            }
            printf("\n");
        }
    }
    printf("End of htab\n");
}
