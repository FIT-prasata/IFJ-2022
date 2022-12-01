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
    /*Token_t *token = malloc(sizeof(Token_t));
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
    free(item);*/
    FILE *file = fopen("./src/adam-test.out", "w");
    if (file == NULL) {
        printf("File not found");
        return 1;
    }
    Token_t *token1 = malloc(sizeof(Token_t));
    token1->attribute.string = "Zadejte cislo pro vypocet faktorialu\n";
    token1->type = T_STRING;

    Token_t *token2 = malloc(sizeof(Token_t));
    token2->attribute.string = "int";
    token2->type = T_INT;

    generate(PROLOG, NULL, NULL, NULL, 0, NO, file);
    generate(WRITE, token1, NULL, NULL, 0, NO, file);
    token1->attribute.string = "$a";
    token1->type = T_ID;
    generate(READ, token1, token2, NULL, 0, GF, file);
    token2->type = K_NULL;
    generate(IF_EQ, token1, token2, NULL, 1, NO, file);
    token1->attribute.string = "Chyba pri nacitani celeho cisla!\n";
    token1->type = T_STRING;
    generate(WRITE, token1, NULL, NULL, 0, NO, file);
    generate(IF_ELSE, NULL, NULL, NULL, 1, NO, file);
    generate(IF_END, NULL, NULL, NULL, 1, NO, file);

    fclose(file);
    return 0;
}
