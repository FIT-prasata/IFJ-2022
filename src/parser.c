// Filename: parser.c
// IFJ 2022/2023 project
// TRP variant
//
// Parser for syntax analysis
//
// Author: <xsklen14> - David Sklenář
// Author: <xproch0o> - Marek Procházka
// Author: <xzavad20> - Lukáš Zavadil
// Author: <xsvetl07> - Adam Světlík

// LOCAL INCLUDES
#include "parser.h"#include "parser.h"

Token_t *init_token(void) {
    Token_t *token = (Token_t *)malloc(sizeof(Token_t));
    if (token == NULL) return NULL;
    token->type = NO_TYPE;
    if ((token->attribute.string = (char *)malloc(sizeof(char))) == NULL) {
        free(token);
        return NULL;
    }
    if (d_string_init(token->attribute.string) != OK) {
        free(token->attribute.string);
        free(token);
        return NULL;
    }
    return token;
}

int free_token(Token_t *token) {
    int status = OK;
    if (token == NULL) return INTERNAL_ERR;
    status |= d_string_free_and_clear(token->attribute.string);
    free(token->attribute.string);
    free(token);
    return status;
}

int parse(void) {
    int status = OK;
    Token_t *token = init_token();
    if (token == NULL) return INTERNAL_ERR;
    Htab_t *global_table = htab_init(50);
    if (global_table == NULL) {
        free_token(token);
        return INTERNAL_ERR;
    }

    scope_t scope_state = {false, false, false, false, false, 0, 0};
    status |= program_rule(token, &scope_state, global_table);
    free_token(token);
    htab_free(global_table);
    return status;
}
