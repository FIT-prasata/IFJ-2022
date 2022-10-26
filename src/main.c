// Filename: main.c
// IFJ 2022/2023 project
// TRP variant
//
// Main file
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
//#include "dynamic_string.h"
#include "error.h"
//#include "stack.h"
#include "symtable.h"

int main(void) {
    int keyword_types[] = {K_ELSE, K_FLOAT, K_FUNC, K_IF, K_INT, K_NULL, K_RET, K_STR, K_VOID, K_WHILE};
    Token_t *token = malloc(sizeof(Token_t));
    string_handler(token);
    printf("hee\n");
    printf("atribut: %s\n", token->attribute.string);
    printf("%c\n", getchar());
    /* adamovy srandy
    htab_t* table = htab_init(10);

    Token_t* token = malloc(sizeof(Token_t));
    token->type = T_ID;
    token->attribute.string = "prdel";

    htab_insert_item(table, token);
    print_table(table);

    Token_t* token2 = malloc(sizeof(Token_t));
    token2->type = T_ID;
    token2->attribute.string = "prdelkaaa";

    htab_item_t* item = htab_find(table, "prdelkaaa");
    if (item != NULL)
        printf("%s\n", item->token->attribute.string);
    else
        printf("kokot\n");
    htab_item_t* item1 = htab_lookup_add(table, token2);
    print_table(table);
    printf("%s\n", item1->token->attribute.string);

    htab_insert_item(table, token);
    print_table(table);

    htab_clear(table);
    print_table(table);
    htab_free(table);
    */
    return 0;
}
