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
    char* tmp[] = {
    "T_UNDEF",     // undefined type
    "T_LT",  // <
    "T_GT",  // >
    "T_LE",  // <=
    "T_GE",  // >=
    "T_EQ",  // ===
    "T_NE",  // !==

    // KEYWORDS
    "K_ELSE",   // else
    "K_FLOAT",  // float
    "K_FLOAT_NULL",  // float with ?
    "K_FUNC",   // function
    "K_IF",     // if
    "K_INT",    // int
    "K_INT_NULL",    // int with ?
    "K_NULL",   // null
    "K_RET",    // return
    "K_STR",    // string
    "K_STR_NULL",    // string with ?
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
    "T_SEM",       // semicolon
    "T_PROLOG1",   // prolog <?php
    "T_PROLOG2",   // prolog declare(strict_types=1);
    "T_END_PROLOG"
    };

    Token_t *token = malloc(sizeof(Token_t));
    if (token == NULL) {
        return INTERNAL_ERR;
    }
    token->attribute.string = NULL;
    token->attribute.value = -1;
    token->attribute.dec_value = -1;
    token->type = T_UNDEF;

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
        if (token->attribute.value != -1) {
            printf("Attribute: %d", token->attribute.value);
            token->attribute.value = -1;
        }
        if (token->attribute.dec_value != -1) {
            printf("Attribute: %f", token->attribute.dec_value);
            token->attribute.dec_value = -1;
        }
        printf("\n");
        if (ret_value != 0) {
            printf("ERROR, ret_value: %d\n", ret_value);
        }
        //free(token);
        //token = malloc(sizeof(Token_t));
        //token->attribute.string = NULL;
    }
    if (token->attribute.string != NULL) {
            free(token->attribute.string);
            token->attribute.string = NULL;
        }
    free(token);

    return 0;
    }


                    // for (int i = 0; i < 2; i++) {
                    //     // get next number of octal (2. and 3.)
                    //     oct_hex-.[i] = getchar();
                    //     oct_hex[i + 1] = '\0';
                    //     // very rare edge case ("...x\x6") - end of string in \ part
                    //     if (oct_hex[i] == '"') {
                    //         num_ok = false;
                    //         curr = '"';
                    //     }
                    //     // check if oct char are in valid range
                    //     if ((oct_hex[i] < '0' || oct_hex[i] > '9') && (oct_hex[i] < 'A' || oct_hex[i] > 'F') && (oct_hex[i] < 'a' || oct_hex[i] > 'f')) {
                    //         // if not, write into string '\' (by instructions)
                    //         d_string_add_char(&dString, '\\');
                    //         d_string_add_char(&dString, 'x');
                    //         for (int j = 0; oct_hex[j] != '\0' && oct_hex[j] != '"'; j++) {
                    //             // insert into string rest of loaded items
                    //             d_string_add_char(&dString, oct_hex[j]);
                    //         }
                    //         num_ok = false;
                    //         break;
                    //     }
                    // }
                    // if (num_ok == true) {
                    //     decimal = strtol(oct_hex, &garbage_strtol, 16);
                    //     d_string_add_char(&dString, (char)decimal);
                    // }
                    // decimal = 0;
                    // num_ok = true;
                    // break;
