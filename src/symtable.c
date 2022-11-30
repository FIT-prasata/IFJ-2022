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


// Hashtable constructor - initializes hashtable
Htab_t *htab_init(size_t size) {
    if (size < 1) {
        return NULL;
    }
    Htab_t *htab_table = malloc(sizeof(Htab_t));
    if (htab_table == NULL) {
        return NULL;
    }
    htab_table->size = 0;
    htab_table->arr_size = size;
    htab_table->arr_ptr = malloc(size * sizeof(Htab_item_t *));
    if (htab_table->arr_ptr == NULL) {
        free(htab_table);
        return NULL;
    }
    for (size_t i = 0; i < size; i++) {
        htab_table->arr_ptr[i] = NULL;
    }
    return htab_table;
}

// Hash function - hash % array size gives table index of item
int htab_hash_function(Htab_key_t key) {
    if (key == NULL) {
        return -1;
    }
    uint32_t h = 0;
    const unsigned char *p;
    for (p = (const unsigned char *)key; *p != '\0'; p++) {
        h = 65599 * h + *p;
    }
    return h;
}

// Inserts item into the hashtable
int htab_insert_item(Htab_t *table, Token_t *token) {
    if (table == NULL || token == NULL) {
        return INTERNAL_ERR;
    }
    Htab_key_t key = token->attribute.string;
    int hash = htab_hash_function(key) % table->arr_size;
    Htab_item_t *item = malloc(sizeof(Htab_item_t));
    if (item == NULL) {
        return INTERNAL_ERR;
    }
    item->data.next = NULL;
    item->data.used = false;
    item->data.name = key;
    if (token->type == T_ID) {
        item->data.type.var.type = NONE;
        item->data.type.var.asigned = false;
    } else if (token->type == T_FUNC_ID) {
        item->data.type.func.argc = 0;
        item->data.type.func.argv = NULL;
        item->data.type.func.return_type = NONE;
    } else {
        free(item);
        return INTERNAL_ERR;
    }
    item->next = NULL;
    Htab_item_t *tmp = table->arr_ptr[hash];
    table->arr_ptr[hash] = item;
    item->next = tmp;
    table->size++;
    return OK;
}

// Finds item in table according to the entered key
Htab_item_t *htab_find(Htab_t *table, Htab_key_t key) {
    if (table == NULL || key == NULL) {
        return NULL;
    }
    int hash = htab_hash_function(key) % table->arr_size;
    Htab_item_t *item = table->arr_ptr[hash];
    while (item != NULL && strcmp(item->data.name, key) != 0) {
        item = item->next;
    }
    if (item == NULL) {
        return NULL;
    }
    return item;
}

// Finds or instert item in table according to the entered key
Htab_item_t *htab_lookup_add(Htab_t *table, Token_t *token) {
    if (table == NULL || token == NULL) {
        return NULL;
    }
    Htab_key_t key = token->attribute.string;
    Htab_item_t *item = htab_find(table, key);
    if (item == NULL) {
        if (htab_insert_item(table, token) == INTERNAL_ERR) {
            return NULL;
        }
        item = htab_find(table, key);
        return item;
    }
    return item;
}

// Deletes item from hashtable according to the entered key
int htab_erase(Htab_t *table, Htab_key_t key) {
    if (table == NULL || key == NULL) {
        return INTERNAL_ERR;
    }
    int hash = htab_hash_function(key) % table->arr_size;
    Htab_item_t *item = table->arr_ptr[hash];
    Htab_item_t *pervious = NULL;
    while (item != NULL && strcmp(item->data.name, key)) {
        pervious = item;
        item = item->next;
    }
    if (item == NULL) {
        return INTERNAL_ERR;
    }
    if (pervious == NULL) {
        table->arr_ptr[hash] = item->next;
    } else {
        pervious->next = item->next;
    }
    free(item);
    table->size--;
    return OK;
}

// Deletes all items from hashtable
int htab_clear(Htab_t *table) {
    if (table == NULL) {
        return INTERNAL_ERR;
    }
    for (size_t i = 0; i < table->arr_size; i++) {
        // size_t size = table->arr_size;
        Htab_item_t *item = table->arr_ptr[i];

        while (item != NULL) {
            if (htab_erase(table, item->data.name) == INTERNAL_ERR) {
                return INTERNAL_ERR;
            }
            item = item->next;
        }
    }
    table->size = 0;
    return OK;
}

// Hashtable destructor - deletes all items and frees allocated memory
int htab_free(Htab_t *table) {
    if (table == NULL) {
        return INTERNAL_ERR;
    }
    if (htab_clear(table) == INTERNAL_ERR) {
        return INTERNAL_ERR;
    }
    free(table->arr_ptr);
    free(table);
    return OK;
}
