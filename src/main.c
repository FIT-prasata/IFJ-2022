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
    CHECK_NULL(file);
    Token_t *token1 = malloc(sizeof(Token_t));
    CHECK_NULL(token1);
    token1->attribute.string = "Zadejte cislo pro vypocet faktorialu\n";
    token1->type = T_STRING;

    CHECK_OK(generate(PROLOG, NULL, NULL, NULL, 0, NO, file));
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, NO, file));

    token1->attribute.string = "$a";
    token1->type = T_ID;
    Token_t *token2 = malloc(sizeof(Token_t));
    CHECK_NULL(token2);
    token2->attribute.string = "int";
    token2->type = T_INT;
    CHECK_OK(generate(DEFVAR, NULL, token1, NULL, 0, GF, file));
    CHECK_OK(generate(READ, token1, token2, NULL, 0, GF, file));
    token2->type = K_NULL;
    CHECK_OK(generate(IF_EQ, NULL, token1, token2, 1, GF, file));
    token1->attribute.string = "Chyba pri nacitani celeho cisla!\n";
    token1->type = T_STRING;
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, NO, file));
    CHECK_OK(generate(IF_ELSE, NULL, NULL, NULL, 1, NO, file));
    CHECK_OK(generate(IF_END, NULL, NULL, NULL, 1, NO, file));
    token1->attribute.string = "$a";
    token1->type = T_ID;
    token2->attribute.string = "0";
    token2->type = T_INT;
    CHECK_OK(generate(IF_LT, NULL, token1, token2, 2, GF, file));
    token1->attribute.string = "Faktorial nelze spocitat\n";
    token1->type = T_STRING;
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, NO, file));
    CHECK_OK(generate(IF_ELSE, NULL, NULL, NULL, 2, NO, file));
    token1->attribute.string = "$vysl";
    token1->type = T_ID;
    CHECK_OK(generate(DEFVAR, NULL, token1, NULL, 0, GF, file));
    token2->attribute.string = "1";
    token2->type = T_INT;
    CHECK_OK(generate(ASSIGN, token1, token2, NULL, 0, GF, file));
    token1->attribute.string = "$a";
    token1->type = T_ID;
    token2->attribute.string = "1";
    token2->type = T_INT;
    CHECK_OK(generate(WHILE_GT, NULL, token1, token2, 1, NO, file));
    token1->attribute.string = "$vysl";
    token1->type = T_ID;
    token2->attribute.string = "$a";
    token2->type = T_ID;
    CHECK_OK(generate(MUL, token1, token1, token2, 0, GF, file));
    token1->attribute.string = "$a";
    token1->type = T_ID;
    token2->attribute.string = "1";
    token2->type = T_INT;
    CHECK_OK(generate(SUB, token1, token1, token2, 0, GF, file));
    CHECK_OK(generate(WHILE_END, NULL, NULL, NULL, 1, NO, file));
    token1->attribute.string = "Vysledek je: ";
    token1->type = T_STRING;
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, GF, file));
    token1->attribute.string = "$vysl";
    token1->type = T_ID;
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, GF, file));
    token1->attribute.string = "\n";
    token1->type = T_STRING;
    CHECK_OK(generate(WRITE, NULL, token1, NULL, 0, NO, file));
    CHECK_OK(generate(IF_END, NULL, NULL, NULL, 2, NO, file));

    free(token1);
    free(token2);
    fclose(file);
    // TODO: frame maybe as a parameter of token
    return OK;
}
