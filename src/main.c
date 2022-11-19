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
    Token_t *token = malloc(sizeof(Token_t));
    if (token == NULL) {
        return INTERNAL_ERR;
    }
    int line_num = 1;
    printf("%d\n", prolog_handler(&line_num));
    printf("line: %d\n", line_num);

    return 0;
    }
