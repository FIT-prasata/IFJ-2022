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
#include "code_generator.h"
#include "symtable.h"

int main(void) {
    Token_t *token = malloc(sizeof(Token_t));
    token->attribute.string = "word word";
    token->type = T_STRING;
    char *tmp = string_convert(token);
    printf("%s", tmp);

    return 0;
}
