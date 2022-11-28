/**
 * @c file main.c
 * @project IFJ 2022/2023
 * @variant TRP
 *
 * @brief Main file
 *
 * @authors <xsklen14> - David Sklenář
 *          <xproch0o> - Marek Procházka
 *          <xzavad20> - Lukáš Zavadil
 *          <xsvetl07> - Adam Světlík
 */

// LOCAL INCLUDES
//#include "dynamic_string.h"
#include "error.h"
//#include "stack.h"
#include "code_generator.h"
#include "symtable.h"

int main(void) {
    Token_t *token = malloc(sizeof(Token_t));
    token->attribute.string = "word#\\word";
    token->type = K_NULL;

    Htab_item_t *item = malloc(sizeof(Htab_item_t));
    item->data.name = "test_var";
    Frame_t frame = GF;

    DString_t string;
    d_string_init(&string);

    int ret = variable_convert(item, frame, &string);
    printf("Var: %d, %s\n", ret, string.str);
    ret = const_convert(token, &string);
    printf("Const: %d, %s\n", ret, string.str);
    ret = string_convert(token, &string);
    printf("String: %d, %s\n", ret, string.str);

    free(token);
    free(item);
    return 0;
}
