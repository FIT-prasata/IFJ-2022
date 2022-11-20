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
    char* tmp[41] = {"T_LT",  // <
    "T_GT",  // >
    "T_LE",  // <=
    "T_GE",  // >=
    "T_EQ",  // ===
    "T_NE",  // !==

    // KEYWORDS
    "K_ELSE",   // else
    "K_FLOAT",  // float
    "K_FUNC",   // function
    "K_IF",     // if
    "K_INT",    // int
    "K_NULL",   // null
    "K_RET",    // return
    "K_STR",    // string
    "K_VOID",   // void
    "K_WHILE",  // while

    // PUNCTUATORS
    "T_LCBR",    // {
    "T_RCBR",    // }
    "T_LBR",     // (
    "T_RBR",     // )
    "T_COL",     // :
    "T_CONCAT",  // .

    // EXPRESSIONS
    "T_MUL",     // *
    "T_DIV",     // /
    "T_ADD",     // +
    "T_SUB",     // -
    "T_ASSIGN",  // =
    "T_NEG",     // !

    // TYPES
    "T_INT",     // integer type
    "T_FLOAT",   // float type
    "T_STRING",  // string type

    // OTHERS
    "T_ID",        // variable identifier
    "T_FUNC_ID",   // function identifier
    "T_EOF",       // end of file
    "T_EOL",       // end of line
    "T_UNDEF",     // undefined type
    "T_SEM",       // semicolon
    "T_KEYWORD",
    "T_PROLOG1",   // prolog <?php
    "T_PROLOG2",   // prolog declare(strict_types=1);
    "T_END_PROLOG"
    };

    Token_t *token = malloc(sizeof(Token_t));
    if (token == NULL) {
        return INTERNAL_ERR;
    }
    token->attribute.string = NULL;

    while(token->type != T_EOF){
        ret_value = scan(token);
        printf("L: %d -- ", line_num);
        printf("Type: %s -- ", tmp[token->type]);
        //printf("Type: %d -- ", token->type);
        if (token->attribute.string != NULL) {
            printf("Attribute: %s", token->attribute.string);
            free(token->attribute.string);
            token->attribute.string = NULL;
        }
        printf("\n");
        //free(token);
        //token = malloc(sizeof(Token_t));
        //token->attribute.string = NULL;
    }

    return 0;
    }
