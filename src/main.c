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

int line_num = 1;

// LOCAL INCLUDES
//#include "dynamic_string.h"
#include "error.h"
//#include "stack.h"
#include "symtable.h"


int main(void) {
    int ret_value;
    Token_t *token = malloc(sizeof(Token_t));
    if (token == NULL) {
        return INTERNAL_ERR;
    }
    while(token->type != T_EOF){
        ret_value = scan(token);
        printf("Type: %d --", token->type);
        printf("line: %d\n", line_num);
    }

    return 0;
    }
