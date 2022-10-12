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
    htab_t* table = htab_init(10);
    Token_t* token = malloc(sizeof(Token_t));
    token->type = T_ID;
    token->attribute.string = "prdel";
    htab_insert_item(table, token);
    print_table(table);
    // table->arr_ptr[5]->token.attribute.string = "abcd";
    // print_table(table);
    return 0;
}
