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
#include "stack.h"
#include "symtable.h"

int main(void) {
    // Testing makefile
    Stack_t stack;
    Token_t token1, token2, result;
    token1.type = 20;
    token2.type = 40;
    stack_init(&stack);
    stack_push(&stack, token1);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);
    stack_push(&stack, token2);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);
    stack_clear(&stack);
    result = stack_get_head(&stack);
    printf("Token: %d\n", result.type);

    htab_t *table = htab_init(10);
    printf("array size: %d\nsize: %d\n", table->arr_size, table->size);

    return 0;
}